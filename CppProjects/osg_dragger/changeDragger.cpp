//http://blog.csdn.net/tmljs1988/archive/2010/10/17/5946593.aspx
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osgManipulator/Command>
#include <osgManipulator/CommandManager>  
#include <osgManipulator/Translate2DDragger>
#include <osgText/Text>

#include <iostream>
#include <string>

#include <osg/ShapeDrawable>

/*#pragma comment( lib, "osgd.lib"); //此库用于Debug版本下
#pragma comment( lib, "osgDBd.lib");
#pragma comment( lib, "osgViewerd.lib");
#pragma comment( lib, "osgmanipulatord.lib");
#pragma comment( lib, "osgTextd.lib");
#pragma comment( lib, "osgGAd.lib");*/

using namespace std;
using namespace osgManipulator;

osg::ref_ptr< osg::Group > g_pRoot= new osg::Group();

class CDraggerPoint: public osgManipulator::Translate2DDragger
{
public:
    void setupDefaultGeometry()
    {
       osg::ref_ptr< osg::Geometry   > pGeom= new osg::Geometry();
       osg::ref_ptr< osg::Geode    > pGeoSphere= new osg::Geode();
       osg::ref_ptr< osg::Vec3Array > pVertices= new osg::Vec3Array(  3);

       int t= 2;

       (*pVertices)[ 0].set( 0, 0+ t, 0);
       (*pVertices)[ 1].set( 0, 0+ t, -2);
       (*pVertices)[ 2].set( 2, 0+ t, 0);

       pGeom->setVertexArray( pVertices.get() );

       osg::ref_ptr< osg::DrawElementsUInt> pTri= new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES , 0);

       pTri->push_back( 0);
       pTri->push_back( 1);
       pTri->push_back( 2);
       pGeom->addPrimitiveSet( pTri.get());

       pGeoSphere->addDrawable( pGeom.get());
       addChild( pGeoSphere.get());
    }

    virtual bool handle(const PointerInfo& pointer, const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
    {
       // Check if the dragger node is in the nodepath.
       if (!pointer.contains(this)) return false;
       switch (ea.getEventType())
       {
           // Pick start.
       case (osgGA::GUIEventAdapter::PUSH):
           {
               // Get the LocalToWorld matrix for this node and set it for the projector.
              osg::NodePath nodePathToRoot;
              computeNodePathToRoot(*this,nodePathToRoot);
              osg::Matrix localToWorld = osg::computeLocalToWorld(nodePathToRoot);
              _projector->setLocalToWorld(localToWorld);

              //设置点移动平面,点即鼠标与物体交点(世界坐标系),法线为//视线方向
			  //osg::Plane::Plane  ( const Vec3_type &  norm,  const Vec3_type &  point) norm:法线；point:交点

              osg::Plane* pplnPTPush= new osg::Plane( pointer.getEyeDir(),
				  pointer.getLocalIntersectPoint()/** _projector->getLocalToWorld()*/);
              _projector->setPlane( *pplnPTPush);

              if (_projector->project(pointer, _startProjectedPoint))
              {
                  // Generate the motion command.
                  osg::ref_ptr<TranslateInPlaneCommand> cmd = new TranslateInPlaneCommand(_projector->getPlane());

                  cmd->setStage(MotionCommand::START);
                  cmd->setReferencePoint(_startProjectedPoint);
                  cmd->setLocalToWorldAndWorldToLocal(_projector->getLocalToWorld(),_projector->getWorldToLocal());

                  // Dispatch command.
                  if (_commandManager)
                  {
                     _commandManager->addSelectionsToCommand(*cmd, *getParentDragger());
                     _commandManager->dispatch(*cmd);
                  }
              //在该点处添加一个球 
              osg::ref_ptr< osg::Shape> sphere = 
				  new osg::Sphere( _startProjectedPoint* _projector->getLocalToWorld(), 0.08f);
              osg::ref_ptr<osg::ShapeDrawable> sphereDrawable = new osg::ShapeDrawable(sphere);
              osg::ref_ptr<osg::Geode> sphereGeode = new osg::Geode();
              sphereGeode->addDrawable(sphereDrawable);

              g_pRoot->addChild( sphereGeode);

                  // Set color to pick color.
                  setMaterialColor(_pickColor,*this);
                  getOrCreateStateSet()->setAttributeAndModes(_polygonOffset.get(), osg::StateAttribute::ON);

                  aa.requestRedraw();
              }
              return true; 
           }

           // Pick move.
       case (osgGA::GUIEventAdapter::DRAG):
           {
              osg::Vec3d projectedPoint;
              if (_projector->project(pointer, projectedPoint))
              {
                  // Generate the motion command.
                  osg::ref_ptr<TranslateInPlaneCommand> cmd = new TranslateInPlaneCommand(_projector->getPlane());

                  cmd->setStage(MotionCommand::MOVE);
                  cmd->setLocalToWorldAndWorldToLocal(_projector->getLocalToWorld(),_projector->getWorldToLocal());
                  cmd->setTranslation(projectedPoint - _startProjectedPoint);
                  cmd->setReferencePoint(_startProjectedPoint);

                  // Dispatch command.
                  if (_commandManager)
                  {
                     _commandManager->addSelectionsToCommand(*cmd, *getParentDragger());
                     _commandManager->dispatch(*cmd);
                  }

				  osg::ref_ptr< osg::Shape> sphere =
					  new osg::Sphere( projectedPoint* _projector->getLocalToWorld(), 0.08f);
              osg::ref_ptr<osg::ShapeDrawable> sphereDrawable = new osg::ShapeDrawable(sphere);
              osg::ref_ptr<osg::Geode> sphereGeode = new osg::Geode();
              sphereGeode->addDrawable(sphereDrawable);

              g_pRoot->addChild( sphereGeode);

                  aa.requestRedraw();
              }
              return true; 
           }

           // Pick finish.
       case (osgGA::GUIEventAdapter::RELEASE):
           {

               osg::ref_ptr<TranslateInPlaneCommand> cmd = new TranslateInPlaneCommand(_projector->getPlane());

               cmd->setStage(MotionCommand::FINISH);
               cmd->setReferencePoint(_startProjectedPoint);
               cmd->setLocalToWorldAndWorldToLocal(_projector->getLocalToWorld(),_projector->getWorldToLocal());

              // Dispatch command.
              if (_commandManager)
              {
                  _commandManager->addSelectionsToCommand(*cmd, *getParentDragger());
                  _commandManager->dispatch(*cmd);
              }
              // Reset color.
              setMaterialColor(_color,*this);
              getOrCreateStateSet()->removeAttribute(_polygonOffset.get());

              aa.requestRedraw();
              return true;
           }
       default:
           return false;
       }
    }
}; 

class PickModeHandler : public osgGA::GUIEventHandler
{
public:
    enum Modes
    {
       VIEW = 0,
       PICK
    };

    PickModeHandler():
       _mode(VIEW), 
          _activeDragger(0)
       {
       }         

       bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa,
           osg::Object*, osg::NodeVisitor*)
       {
           osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
           if (!view) return false; 

           if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Tab &&
              ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN &&
              _activeDragger == 0)
           {
              _mode = ! _mode;
           }

           if (VIEW == _mode) return false; 

           switch (ea.getEventType())
           {
           case osgGA::GUIEventAdapter::PUSH:
              {
                  osgUtil::LineSegmentIntersector::Intersections intersections;

                  _pointer.reset();
                  if (view->computeIntersections(ea.getX(),ea.getY(),intersections))
                  {
                     _pointer.setCamera(view->getCamera());
                     _pointer.setMousePosition(ea.getX(), ea.getY());

                     for(osgUtil::LineSegmentIntersector::Intersections::iterator hitr = intersections.begin();
                         hitr != intersections.end(); ++hitr)
                     {
                         _pointer.addIntersection(hitr->nodePath, hitr->getLocalIntersectPoint());
                     }
                     for (osg::NodePath::iterator itr = _pointer._hitList.front().first.begin();
                         itr != _pointer._hitList.front().first.end();
                         ++itr)
                     {
                         osgManipulator::Dragger* dragger = dynamic_cast<osgManipulator::Dragger*>(*itr);
                         if (dragger)
                         {

                            dragger->handle(_pointer, ea, aa);
                            _activeDragger = dragger;

                            break; 
                         }                    
                     }
                  }

              }
           case osgGA::GUIEventAdapter::DRAG:
           case osgGA::GUIEventAdapter::RELEASE:
			   {
                  if (_activeDragger)
                  {
                     _pointer._hitIter = _pointer._hitList.begin();
                     _pointer.setCamera(view->getCamera());
                     _pointer.setMousePosition(ea.getX(), ea.getY());

                     _activeDragger->handle(_pointer, ea, aa);
                  }
                 break;
              }
           default:
              break;
           }

           if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
           {
              _activeDragger = 0;
              _pointer.reset();
           }

           return true;
       }


private:
    unsigned int _mode;
    osgManipulator::Dragger* _activeDragger;
    osgManipulator::PointerInfo _pointer;
};


osgManipulator::Dragger* createDragger(const std::string& name)
{
    osgManipulator::Dragger* dragger = 0;

    CDraggerPoint* d = new CDraggerPoint();
    d->setupDefaultGeometry();
    dragger = d;

    return dragger;
}

osg::Node* addDraggerToScene(osg::Node* scene, osgManipulator::CommandManager* cmdMgr, const std::string& name)
{
    scene->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);

    osgManipulator::Selection* selection = new osgManipulator::Selection;
    selection->addChild(scene);

    osgManipulator::Dragger* dragger = createDragger(name);
    dragger->setName( name);

    osg::Group* root = new osg::Group;
    root->addChild(dragger);
    root->addChild(selection);


    cmdMgr->connect(*dragger, *selection);

    return root;
}


int main()
{

    osg::ref_ptr< osg::Geode    > pGeoSphere= new osg::Geode();
    osg::ref_ptr< osg::Geometry   > pGeom= new osg::Geometry();

    osg::ref_ptr< osg::Vec3Array > pVertices= new osg::Vec3Array(  3);

    (*pVertices)[ 0].set( 0+ 2, 0- 2, 0);
    (*pVertices)[ 1].set( 0 , 0- 2, 2);
    (*pVertices)[ 2].set( 0, 0- 2, 0);
    pGeom->setVertexArray( pVertices.get() );

    osg::ref_ptr< osg::DrawElementsUInt> pTri= new osg::DrawElementsUInt( osg::PrimitiveSet::TRIANGLES , 0);

    pTri->push_back( 0);
    pTri->push_back( 1);
    pTri->push_back( 2);
    pGeom->addPrimitiveSet( pTri.get());


    pGeoSphere->addDrawable( pGeom.get());


    //g_pRoot->addChild( pGeoSphere.get());//将非dragger的物体加入

    osgViewer::Viewer viewer;

    //cmdManager
    osg::ref_ptr<osgManipulator::CommandManager> cmdMgr = new osgManipulator::CommandManager;

	osg::ref_ptr< osg::Geode    > pGeoSphereDragger= new osg::Geode();
    g_pRoot->addChild(addDraggerToScene( pGeoSphereDragger.get(),cmdMgr,"Translate2DDragger") );

    viewer.setSceneData(  g_pRoot);

    viewer.addEventHandler(new PickModeHandler());

    return viewer.run();  
}
