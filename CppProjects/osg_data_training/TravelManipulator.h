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
	//bool m_pengFlag;//��ײ����־λ��Ĭ��Ϊ��ײ��⿪��

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
	//void mouseDouClickHandle(float x, float y);//����һ��¼� ˫��
	//bool judgeCameraAndNode(osg::Camera* currentcamera, osg::MatrixTransform* currentnode);//�ж��ӵ�
	//void adjustCameraDirection(osg::Camera* currentcamera, osg::MatrixTransform* currentnode);//�����ӵ�
};
