#include "MouseHandler.h"

CMouseHandler::CMouseHandler(osgText::Text * updateText)
{
	_updateText = updateText;
}

CMouseHandler::~CMouseHandler(void)
{
}

/*int CMouseHandler::convertCStringToInt(CString tempcstring)
{
	char* tempchar =tempcstring.GetBuffer(tempcstring.GetLength());
	int tempint = atoi(tempchar);
	return tempint;
}

int CMouseHandler::convertStringToInt(std::string tempstring)
{
	CString temporaryCString = tempstring.c_str();
	return convertCStringToInt(temporaryCString);
}*/

bool CMouseHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
		case osgGA::GUIEventAdapter::PUSH://�����������¼�����Ӧ����������
			if(ea.getButton()==1)
			{
				mouseLeftClickHandle(ea.getX(),ea.getY());
			}
			break;
		case (osgGA::GUIEventAdapter::FRAME):
			{
				osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*> (&aa);
				viewer->getCamera()->getViewMatrixAsLookAt(position, center, up);
				if(viewer)
					refreshHUD(viewer, ea);
			}
			break;
		case(osgGA::GUIEventAdapter::DOUBLECLICK):
			{
				if(ea.getButton()==1)//���˫��
				{
					mouseDouClickHandle(ea.getX(),ea.getY());//�����Ǵ����ĸ��׶Σ�˫���������ӵ㿿��
					return true;
				}
				return false;
			}
		default:
			break;
	}
	
	return false;
}

void CMouseHandler::refreshHUD(osgViewer::Viewer* viewer, const osgGA::GUIEventAdapter& ea){
	//osgUtil::LineSegmentIntersector::Intersections intersections;
	string gdlist="";
	ostringstream os;
	os<<"Position X:"<<position[0]<<"        Y:"<<position[1]<<"        Z:"<<position[2]<<endl;
	os<<"Center X:"<<center[0]<<"        Y:"<<center[1]<<"        Z:"<<center[2]<<endl;
	os<<"Up X:"<<up[0]<<"        Y:"<<up[1]<<"        Z:"<<up[2];
	
	gdlist += os.str();
	setLabel(gdlist);

	
}

void CMouseHandler::mouseLeftClickHandle(float x, float y)
{
	
}

void CMouseHandler::mouseDouClickHandle(float x, float y)
{
}

