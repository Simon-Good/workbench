//PickModelHandler.cpp，PickModelHandler类
#include "PickModelHandler.h"
PickModelHandler::PickModelHandler(osg::ref_ptr<osg::Group>givenRoot){
	manager = new osgManipulator::CommandManager;
	selection = new osgManipulator::Selection;
	dragger=new osgManipulator::TranslateAxisDragger();
	//selections = new osgManipulator::CommandManager::Selections;
	//grandfather = new osg::Group();
	root = givenRoot;
	node = new osg::Node();
    parent = new osg::MatrixTransform();
}
PickModelHandler::~PickModelHandler(void){
}
bool PickModelHandler::handle(const osgGA::GUIEventAdapter& ea,
								osgGA::GUIActionAdapter& aa){
		osg::ref_ptr<osgViewer::View> view=dynamic_cast<osgViewer::View*>(&aa);
		if(!view)return false;
		switch(ea.getEventType()){
		case osgGA::GUIEventAdapter::DOUBLECLICK:
			{
				if(ea.getButton()==1){
					osgUtil::LineSegmentIntersector::Intersections hits;

					if(view->computeIntersections(ea.getX(),ea.getY(),hits)){
						osgUtil::LineSegmentIntersector::Intersection intersection = *hits.begin();
						osg::NodePath& nodePath = intersection.nodePath;

						node = (nodePath.size()>=1)?nodePath[nodePath.size()-1]:0;
						parent = (nodePath.size()>=2)?dynamic_cast<osg::MatrixTransform*>(nodePath[nodePath.size()-2]):0;
						
						if(parent.get()&&node.get()){//如果node是一个模型零件，那么parent应该是一个selection类型节点
							selections = manager->getConnectedSelections(*dragger);
							if(!selections.empty()){
								selection = selections.front();
								if(node->getName()==selection->getChild(0)->getName()){
									manager->disconnect(*dragger);
									root->removeChild(dragger);
									break;
								}
							}
							float scale=node->getBound().radius()*1.2;
							manager->disconnect(*dragger);
							dragger->setupDefaultGeometry();
							dragger->setName("dragger");
							dragger->setMatrix(osg::Matrix::scale(scale,scale,scale)*
												osg::Matrix::translate(parent->getBound().center()));
							
							root->addChild(dragger.get());
							manager->connect(*dragger,*parent);
						}
					}else{
						manager->disconnect(*dragger);
						root->removeChild(dragger);
					}
				}
			}
			break;
		case osgGA::GUIEventAdapter::PUSH:
			{
				_pointer.reset();
				osgUtil::LineSegmentIntersector::Intersections hits;
				if(view->computeIntersections(ea.getX(),ea.getY(),hits)){
					_pointer.setCamera(view->getCamera());
					_pointer.setMousePosition(ea.getX(),ea.getY());
					osgUtil::LineSegmentIntersector::Intersections::iterator hitr;
					for(hitr=hits.begin();hitr!=hits.end();++hitr){
						_pointer.addIntersection(hitr->nodePath,
							hitr->getLocalIntersectPoint());
					}
					osg::NodePath::iterator itr;
					for(itr=_pointer._hitList.front().first.begin();
						itr!=_pointer._hitList.front().first.end();++itr){
						dragger_pick=dynamic_cast<osgManipulator::Dragger*>(*itr);
						if(dragger){
							dragger->handle(_pointer,ea,aa);
							_activeDragger=dragger;
							break;
						}
					}
				}
				break;
			}
		case osgGA::GUIEventAdapter::DRAG:
		case osgGA::GUIEventAdapter::RELEASE:
			{
				if(_activeDragger){
					_pointer._hitIter=_pointer._hitList.begin();
					_pointer.setCamera(view->getCamera());
					_pointer.setMousePosition(ea.getX(),ea.getY());
					_activeDragger->handle(_pointer,ea,aa);
				}
				if(ea.getEventType()==osgGA::GUIEventAdapter::RELEASE){
					_activeDragger=NULL;
					_pointer.reset();
				}
				break;
			}
		default:break;
		}
		return true;
}
