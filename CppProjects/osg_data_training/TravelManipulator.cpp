#include "TravelManipulator.h"

CTravelManipulator::CTravelManipulator(osgViewer::Viewer* currentViewer):m_fMoveSpeed(5.0f),m_fAngle(2.5f)
{
	m_vPosition = osg::Vec3(175.0f,35.0f,90.0f);//初始位置
	m_vRotation = osg::Vec3(osg::PI_2*0.8, 0.0f,osg::PI_2);//初始角度	
	m_viewer = currentViewer;
	m_firstFloor = true;//初始化情况，视点是在第一楼层即地面一层
	//m_pengFlag = true;//默认开启
}

CTravelManipulator::~CTravelManipulator(void)
{
	//这个viewer是从外部传入的，因此在该类中无需考虑viewer的析构问题，应由CCoreOSG类来完成
}

void CTravelManipulator::setByMatrix(const osg::Matrixd& matrix)
{
}

void CTravelManipulator::setByInverseMatrix(const osg::Matrixd& matrix)
{
}

osg::Matrixd CTravelManipulator::getMatrix(void) const
{
	osg::Matrixd mat;

	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),

		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),

		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));

	return mat * osg::Matrixd::translate(m_vPosition);
}

osg::Matrixd CTravelManipulator::getInverseMatrix(void) const
{
	osg::Matrixd mat;

	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),

		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),

		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));

	return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_vPosition));
}

void CTravelManipulator::ChangePosition(osg::Vec3& delta)
{
	osg::Vec3 newPos = m_vPosition + delta; 
	osgUtil::IntersectVisitor iv; 
	osg::ref_ptr<osg::LineSegment> line = new osg::LineSegment(newPos,m_vPosition); 
	iv.addLineSegment (line.get()) ;
	m_viewer->getSceneData()->accept(iv); 

	/*if(m_pengFlag == true)//如果碰撞检测开启的话就保持原来的方式
	{
		if (!iv.hits()) 
		{ 
			m_vPosition += delta; 
		}
	}
	else
	{*/
		m_vPosition += delta; //如果碰撞检测关闭的话就不管怎样都能够前进
	//}
	
}

void CTravelManipulator::renewMyCamera(void)
{
	//m_vPosition = osg::Vec3(100.0f, 0.0f,190.0f);//初始位置
	//m_vRotation = osg::Vec3(osg::PI_2, 0.0f, -osg::PI_2);	//初始角度
}

/*int CTravelManipulator::convertCStringToInt(CString tempcstring)
{
	char* tempchar =tempcstring.GetBuffer(tempcstring.GetLength());
	int tempint = atoi(tempchar);
	return tempint;
}*/

/*int CTravelManipulator::convertStringToInt(std::string tempstring)
{
	CString temporaryCString = tempstring.c_str();
	return convertCStringToInt(temporaryCString);
}*/

bool CTravelManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	switch(ea.getEventType())
	{
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				if(ea.getKey() == 0XFF50)//home键
				{
					renewMyCamera();
					return true;
				}
				if (ea.getKey() == 0xFF55)//page_up键，视点笔直向上走
				{
					ChangePosition(osg::Vec3 (0, 0, m_fMoveSpeed)) ;
					return true;
				}
				if (ea.getKey() == 0xFF56)//page_down，视点笔直向下走
				{
					ChangePosition(osg::Vec3 (0, 0, -m_fMoveSpeed)) ;
					return true;
				}
				if(ea.getKey() == 0XFF52)//向上键，视点向上仰视
				{
					m_vRotation._v[0] += osg::DegreesToRadians(m_fAngle);
					return true;
				}
				if(ea.getKey () == 0XFF54)//向下键，视点向下俯视
				{
					m_vRotation._v[0] -= osg::DegreesToRadians(m_fAngle);
					return true;
				}
				if (ea.getKey () == 0x41 || ea.getKey () == 0x61)//大写和小写的A键，视点向左平移（当前朝向向左）
				{
					ChangePosition(osg::Vec3 (0, m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (-m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if (ea.getKey () == 0x44||ea.getKey () == 0x64)//大写和小写的d键，视点向右平移（当前朝向向右）
				{
					ChangePosition(osg::Vec3 (0,-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if (ea.getKey() == 0xFF53)//Right，向右旋转，旋转点为当时位置
				{
					m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
				}
				if (ea.getKey()== 0xFF51)//Left，向左旋转，旋转点为当时位置
				{
					m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);
				}
				if(ea.getKey()==0X57 || ea.getKey()==0X77)//w键，向前
				{
					ChangePosition(osg::Vec3 (0, m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if(ea.getKey()==0X53 || ea.getKey()==0X73 )//S键，向后退
				{
					ChangePosition(osg::Vec3 (0, -m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				/*if(ea.getKey()==0X43 || ea.getKey()==0X63 )//C键，切换视角的楼层
				{
					if(m_firstFloor == true)//原来在地面第一层的话，要转换到地下一层
					{
						m_vPosition = osg::Vec3(-50.0f,230.0f,-220.0f);//初始位置
						m_vRotation = osg::Vec3(osg::PI_2, 0.0f,(osg::PI_4)*3.7f);//初始角度
						m_firstFloor = false;
					}
					else//如果在地下一层的话就切换到地面上
					{
						m_vPosition = osg::Vec3(100.0f,0.0f,190.0f);//初始位置
						m_vRotation = osg::Vec3(osg::PI_2, 0.0f,-osg::PI_2);//初始角度
						m_firstFloor = true;
					}
					return true;
				}*/
				/*if(ea.getKey()==0X50  || ea.getKey()==0X70)//P键，切换碰撞检测标志位
				{
					m_pengFlag = !m_pengFlag;//将碰撞标志位置反
					return true;
				}*/

				return false;
			}
		case(osgGA::GUIEventAdapter::SCROLL):
			{
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)//鼠标滑轮向上，应该处理视点后退事件
				{
					ChangePosition(osg::Vec3 (0, -3 * m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3(-3 * m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)//鼠标滑轮向下，应该处理视点前进事件
				{
					ChangePosition(osg::Vec3 (0, 3 * m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (3 * m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				
				return false;//默认返回值
			}
		default:
			return false;
	}
}

/*void CTravelManipulator::mouseDouClickHandle(float x, float y)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;
	osgUtil::LineSegmentIntersector::Intersection intersection;

	if(m_viewer->computeIntersections(x,y,intersections))//如果有交点的话
	{
		const char* mtjiedian = "MatrixTransform";
		intersection =*(intersections.begin());//只取第一个射线相交的物体
		osg::NodePath nodePath;
		nodePath = intersection.nodePath;//第一个射线相交物体的路径

		for(osg::NodePath::iterator myiteratorNode = nodePath.begin();myiteratorNode!= nodePath.end();myiteratorNode++)//遍历这个相交节点的所有路径上的点
		{
			if(strcmp((*myiteratorNode)->className(),mtjiedian)==0)//找到路径上的第一个mt节点，直接就算这个mt的编号看对不对
			{
				//如果找到这个mt之后就进行双击视点前进的函数
				if((convertStringToInt(dynamic_cast<osg::MatrixTransform*>(*myiteratorNode)->getName())>1  &&
					convertStringToInt(dynamic_cast<osg::MatrixTransform*>(*myiteratorNode)->getName())<1001) || 
					convertStringToInt(dynamic_cast<osg::MatrixTransform*>(*myiteratorNode)->getName())<0)//小于0是专门为了包围盒考虑的
					//节点编号从2-1000，包括公共部分（除厂房）+零件部分，区域部分不需要进行视点双击靠近
				{
					//如果目前的视点位置在相机范围之内，就不要进行相机位置的调整了，如果不在就需要进行位置调整
					if(judgeCameraAndNode(m_viewer->getCamera(),dynamic_cast<osg::MatrixTransform*>(*myiteratorNode)))//如果靠近视点，则不需要做任何调整
					{
						//在相机范围内，就不需要做任何的调整
					}
					else//如果不靠近视点，则进行视点位置的调整
					{
						adjustCameraDirection(m_viewer->getCamera(),dynamic_cast<osg::MatrixTransform*>(*myiteratorNode));//调整视点
					}
					break;
				}
				else
				{
					
					break;
				}

			}
			else
			{
				//继续找这个路径上的节点
			}
		}
	}

}*/

/*bool CTravelManipulator::judgeCameraAndNode(osg::Camera* currentcamera, osg::MatrixTransform* currentnode)
{
	osg::Vec3 cameraEye;
	osg::Vec3 toCenter;
	osg::Vec3 cameraUp;
	osg::Vec3 nodePos;

	currentcamera->getViewMatrixAsLookAt(cameraEye,toCenter,cameraUp);//获取到当前照相机的位置
	nodePos = currentnode->getMatrix().getTrans();//获取当前mt下面挂的节点的位置
	nodePos.z() = cameraEye.z();//依旧提到同一个水平面上来，即保持Z值相等

	if(((cameraEye.x()-nodePos.x())*(cameraEye.x()-nodePos.x())+(cameraEye.y()-nodePos.y())*(cameraEye.y()-nodePos.y())+(cameraEye.z()-nodePos.z())*(cameraEye.z()-nodePos.z()))>490000)//说明离开的远了
	{
		return false;//如果远离视点则返回false
	}
	else
	{
		return true;//如果靠近视点则返回true
	}
}

void CTravelManipulator::adjustCameraDirection(osg::Camera* currentcamera, osg::MatrixTransform* currentnode)
{
	osg::Vec3 cameraEye;
	osg::Vec3 toCenter;
	osg::Vec3 cameraUp;
	osg::Vec3 nodePos;

	currentcamera->getViewMatrixAsLookAt(cameraEye,toCenter,cameraUp);//获取到当前照相机的位置
	toCenter.z()=cameraEye.z();//将toCenter的这个方向向量统一保持到水平状态，没有上下倾斜的幅度
	nodePos = currentnode->getMatrix().getTrans();//获取当前mt下面挂的节点的位置

	osg::Vec3 curCameraDirection;
	osg::Vec3 tarCameraDirection;


	curCameraDirection = toCenter - cameraEye;//当前的camera的方向
	curCameraDirection.normalize();
	osg::Vec3 nodePosToSameZ(nodePos.x(),nodePos.y(),cameraEye.z());//将这个nodePos点的z值提升至和当前的相机一个平面，该平面平行与XOY平面
	tarCameraDirection = nodePosToSameZ-cameraEye;//目标camera方向
	tarCameraDirection.normalize();

	float fenzi=curCameraDirection.x()*tarCameraDirection.x()+curCameraDirection.y()*tarCameraDirection.y();
	float fenmu=(sqrt(curCameraDirection.x()*curCameraDirection.x()+curCameraDirection.y()*curCameraDirection.y()))*(sqrt(tarCameraDirection.x()*tarCameraDirection.x()+tarCameraDirection.y()*tarCameraDirection.y()));
	float result = fenzi/fenmu;
	float fai = acos(result);


	//计算从当前camera到目标camera的到角大小
	if((curCameraDirection.x()*tarCameraDirection.y()-tarCameraDirection.x()*curCameraDirection.y())<0)//根据外积来判别是顺时针转动还是逆时针转动，小于0顺时针
	{
		m_vRotation._v[2] -= fai;
	}
	else//大于0逆时针
	{
		m_vRotation._v[2] += fai;
	}

	float totalDistance = sqrt((cameraEye.x()-nodePosToSameZ.x())*(cameraEye.x()-nodePosToSameZ.x())+(cameraEye.y()-nodePosToSameZ.y())*(cameraEye.y()-nodePosToSameZ.y())+(cameraEye.z()-nodePosToSameZ.z())*(cameraEye.z()-nodePosToSameZ.z()));
	float moveDistance = totalDistance - 700;

	ChangePosition(osg::Vec3 (0, moveDistance* sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
	ChangePosition(osg::Vec3 (moveDistance * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;


}*/
