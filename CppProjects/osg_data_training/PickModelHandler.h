//PickModelHandler.h,PickModelHandler类头
#pragma once
#include <osgManipulator/CommandManager>
#include <osgManipulator/TrackballDragger>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgManipulator/Selection>
#include <osgManipulator/CommandManager>
#include <osgManipulator/TranslateAxisDragger>
//#include <osg/ValueObject>

#include <iostream>
using namespace std;
class PickModelHandler:public osgGA::GUIEventHandler{
public:
	PickModelHandler(osg::ref_ptr<osg::Group>givenRoot);
	~PickModelHandler(void);
	bool handle(const osgGA::GUIEventAdapter& ea,
		        osgGA::GUIActionAdapter& aa);
protected:
	osg::ref_ptr<osgManipulator::Dragger>dragger_pick;
	osg::ref_ptr<osgManipulator::Dragger> _activeDragger;
	osgManipulator::PointerInfo _pointer;

	osg::ref_ptr<osgManipulator::CommandManager>manager;
	osg::ref_ptr<osgManipulator::Selection>selection;
	std::list< osg::ref_ptr<osg::MatrixTransform>> selections;
	osg::ref_ptr<osgManipulator::TranslateAxisDragger>dragger;
	osg::ref_ptr<osg::Node> node;
	osg::ref_ptr<osg::MatrixTransform> parent;
	osg::ref_ptr<osg::Group> root;

};
