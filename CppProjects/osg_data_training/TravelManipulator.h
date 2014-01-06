#pragma once

#include <osgViewer/Viewer>
#include <osgGA/CameraManipulator>
#include <osgUtil/IntersectVisitor>
#include <osg/LineSegment>
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <cmath>
#include <Windows.h>


class CTravelManipulator :
	public osgGA::CameraManipulator
{
public:
	CTravelManipulator(osgViewer::Viewer* currentViewer);
	~CTravelManipulator(void);

protected:
	float   m_fMoveSpeed;
	osg::Vec3    m_vPosition;
	osg::Vec3    m_vRotation;
	float m_fAngle;
	osgViewer::Viewer* m_viewer;
	bool m_firstFloor;
	//bool m_pengFlag;//碰撞检测标志位，默认为碰撞检测开启

public:
	virtual void setByMatrix(const osg::Matrixd& matrix);
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	virtual osg::Matrixd getMatrix(void) const;
	virtual osg::Matrixd getInverseMatrix(void) const;
	void ChangePosition(osg::Vec3& delta);
	void renewMyCamera(void);
	//int convertCStringToInt(CString tempcstring);
	//int convertStringToInt(std::string tempstring);
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
	//void mouseDouClickHandle(float x, float y);//鼠标右击事件 双击
	//bool judgeCameraAndNode(osg::Camera* currentcamera, osg::MatrixTransform* currentnode);//判断视点
	//void adjustCameraDirection(osg::Camera* currentcamera, osg::MatrixTransform* currentnode);//调整视点
};
