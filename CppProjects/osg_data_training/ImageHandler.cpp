#include "ImageHandler.h"

ImageHandler::ImageHandler(){
	image_c = new osg::Image;
}

bool ImageHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		osg::ref_ptr<osgViewer::Viewer> viewer = dynamic_cast<osgViewer::Viewer*> (&aa);
		
		if(viewer==NULL)
			return false;

		static int screenCaptureSequence=0;
		
		switch(ea.getEventType()){
		case osgGA::GUIEventAdapter::KEYDOWN:
			{
				if(ea.getKey()=='c' || ea.getKey()== 'C')
				{
					char filename[128];
					sprintf(filename, "ScreenShot%04d.bmp", screenCaptureSequence);;
					screenCaptureSequence++;
					osgDB::writeImageFile(*(image_c.get()), filename);
				}
			}
			break;
		default:
			return false;
		}
		return true;
	}
