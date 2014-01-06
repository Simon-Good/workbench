#pragma once
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Group>
#include <osg/Camera>
#include <osg/Matrix>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>
#include <osgText/Text>
#include <osgText/Font>

#include <iostream>

#include <string>

using namespace std;
class HUD
{
public:
	HUD(void);
	~HUD(void);
	osg::ref_ptr<osg::Camera> createHUDText();

public:
	osg::ref_ptr<osgText::Text> text;
	
};

