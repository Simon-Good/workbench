#pragma once
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/GUIEventAdapter>

#include <stdio.h>
#include <stdlib.h>

class ImageHandler : public osgGA::GUIEventHandler
{
public:
	ImageHandler();
	~ImageHandler(){}
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
public:
	osg::ref_ptr<osg::Image> image_c;
	
};

