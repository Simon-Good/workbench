#pragma once
#include <osg/ComputeBoundsVisitor>
#include <osg/BoundingBox>
#include <osgGA/GUIEventHandler>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class CMouseHandler :
	public osgGA::GUIEventHandler
{
public:
	CMouseHandler(osgText::Text *updateText);
	~CMouseHandler(void);
public:
    //CCoreOSG* currentOSG;//���ⲿ�����osg�ĺ���ָ�룬��GlobalOSG�е�mOSG
	//int convertCStringToInt(CString tempcstring);
	//int convertStringToInt(std::string tempstring);
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);//������
	void mouseLeftClickHandle(float x, float y);
	void refreshHUD(osgViewer::Viewer* viewer, const osgGA::GUIEventAdapter& ea);
	void mouseDouClickHandle(float x, float y);
	void setLabel(const string& name){
		if(_updateText.get()) _updateText->setText(name);
	}

private:
	osg::Vec3 position;
	osg::Vec3 center;
	osg::Vec3 up;
	osg::ref_ptr<osgText::Text> _updateText;
};
