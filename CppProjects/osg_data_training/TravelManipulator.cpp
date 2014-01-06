#include "TravelManipulator.h"

CTravelManipulator::CTravelManipulator(osgViewer::Viewer* currentViewer):m_fMoveSpeed(5.0f),m_fAngle(2.5f)
{
	m_vPosition = osg::Vec3(175.0f,35.0f,90.0f);//��ʼλ��
	m_vRotation = osg::Vec3(osg::PI_2*0.8, 0.0f,osg::PI_2);//��ʼ�Ƕ�	
	m_viewer = currentViewer;
	m_firstFloor = true;//��ʼ��������ӵ����ڵ�һ¥�㼴����һ��
	//m_pengFlag = true;//Ĭ�Ͽ���
}

CTravelManipulator::~CTravelManipulator(void)
{
	//���viewer�Ǵ��ⲿ����ģ�����ڸ��������迼��viewer���������⣬Ӧ��CCoreOSG�������
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

	/*if(m_pengFlag == true)//�����ײ��⿪���Ļ��ͱ���ԭ���ķ�ʽ
	{
		if (!iv.hits()) 
		{ 
			m_vPosition += delta; 
		}
	}
	else
	{*/
		m_vPosition += delta; //�����ײ���رյĻ��Ͳ����������ܹ�ǰ��
	//}
	
}

void CTravelManipulator::renewMyCamera(void)
{
	//m_vPosition = osg::Vec3(100.0f, 0.0f,190.0f);//��ʼλ��
	//m_vRotation = osg::Vec3(osg::PI_2, 0.0f, -osg::PI_2);	//��ʼ�Ƕ�
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
				if(ea.getKey() == 0XFF50)//home��
				{
					renewMyCamera();
					return true;
				}
				if (ea.getKey() == 0xFF55)//page_up�����ӵ��ֱ������
				{
					ChangePosition(osg::Vec3 (0, 0, m_fMoveSpeed)) ;
					return true;
				}
				if (ea.getKey() == 0xFF56)//page_down���ӵ��ֱ������
				{
					ChangePosition(osg::Vec3 (0, 0, -m_fMoveSpeed)) ;
					return true;
				}
				if(ea.getKey() == 0XFF52)//���ϼ����ӵ���������
				{
					m_vRotation._v[0] += osg::DegreesToRadians(m_fAngle);
					return true;
				}
				if(ea.getKey () == 0XFF54)//���¼����ӵ����¸���
				{
					m_vRotation._v[0] -= osg::DegreesToRadians(m_fAngle);
					return true;
				}
				if (ea.getKey () == 0x41 || ea.getKey () == 0x61)//��д��Сд��A�����ӵ�����ƽ�ƣ���ǰ��������
				{
					ChangePosition(osg::Vec3 (0, m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (-m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if (ea.getKey () == 0x44||ea.getKey () == 0x64)//��д��Сд��d�����ӵ�����ƽ�ƣ���ǰ�������ң�
				{
					ChangePosition(osg::Vec3 (0,-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if (ea.getKey() == 0xFF53)//Right��������ת����ת��Ϊ��ʱλ��
				{
					m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
				}
				if (ea.getKey()== 0xFF51)//Left��������ת����ת��Ϊ��ʱλ��
				{
					m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);
				}
				if(ea.getKey()==0X57 || ea.getKey()==0X77)//w������ǰ
				{
					ChangePosition(osg::Vec3 (0, m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if(ea.getKey()==0X53 || ea.getKey()==0X73 )//S���������
				{
					ChangePosition(osg::Vec3 (0, -m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				/*if(ea.getKey()==0X43 || ea.getKey()==0X63 )//C�����л��ӽǵ�¥��
				{
					if(m_firstFloor == true)//ԭ���ڵ����һ��Ļ���Ҫת��������һ��
					{
						m_vPosition = osg::Vec3(-50.0f,230.0f,-220.0f);//��ʼλ��
						m_vRotation = osg::Vec3(osg::PI_2, 0.0f,(osg::PI_4)*3.7f);//��ʼ�Ƕ�
						m_firstFloor = false;
					}
					else//����ڵ���һ��Ļ����л���������
					{
						m_vPosition = osg::Vec3(100.0f,0.0f,190.0f);//��ʼλ��
						m_vRotation = osg::Vec3(osg::PI_2, 0.0f,-osg::PI_2);//��ʼ�Ƕ�
						m_firstFloor = true;
					}
					return true;
				}*/
				/*if(ea.getKey()==0X50  || ea.getKey()==0X70)//P�����л���ײ����־λ
				{
					m_pengFlag = !m_pengFlag;//����ײ��־λ�÷�
					return true;
				}*/

				return false;
			}
		case(osgGA::GUIEventAdapter::SCROLL):
			{
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)//��껬�����ϣ�Ӧ�ô����ӵ�����¼�
				{
					ChangePosition(osg::Vec3 (0, -3 * m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3(-3 * m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)//��껬�����£�Ӧ�ô����ӵ�ǰ���¼�
				{
					ChangePosition(osg::Vec3 (0, 3 * m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (3 * m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				
				return false;//Ĭ�Ϸ���ֵ
			}
		default:
			return false;
	}
}

/*void CTravelManipulator::mouseDouClickHandle(float x, float y)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;
	osgUtil::LineSegmentIntersector::Intersection intersection;

	if(m_viewer->computeIntersections(x,y,intersections))//����н���Ļ�
	{
		const char* mtjiedian = "MatrixTransform";
		intersection =*(intersections.begin());//ֻȡ��һ�������ཻ������
		osg::NodePath nodePath;
		nodePath = intersection.nodePath;//��һ�������ཻ�����·��

		for(osg::NodePath::iterator myiteratorNode = nodePath.begin();myiteratorNode!= nodePath.end();myiteratorNode++)//��������ཻ�ڵ������·���ϵĵ�
		{
			if(strcmp((*myiteratorNode)->className(),mtjiedian)==0)//�ҵ�·���ϵĵ�һ��mt�ڵ㣬ֱ�Ӿ������mt�ı�ſ��Բ���
			{
				//����ҵ����mt֮��ͽ���˫���ӵ�ǰ���ĺ���
				if((convertStringToInt(dynamic_cast<osg::MatrixTransform*>(*myiteratorNode)->getName())>1  &&
					convertStringToInt(dynamic_cast<osg::MatrixTransform*>(*myiteratorNode)->getName())<1001) || 
					convertStringToInt(dynamic_cast<osg::MatrixTransform*>(*myiteratorNode)->getName())<0)//С��0��ר��Ϊ�˰�Χ�п��ǵ�
					//�ڵ��Ŵ�2-1000�������������֣���������+������֣����򲿷ֲ���Ҫ�����ӵ�˫������
				{
					//���Ŀǰ���ӵ�λ���������Χ֮�ڣ��Ͳ�Ҫ�������λ�õĵ����ˣ�������ھ���Ҫ����λ�õ���
					if(judgeCameraAndNode(m_viewer->getCamera(),dynamic_cast<osg::MatrixTransform*>(*myiteratorNode)))//��������ӵ㣬����Ҫ���κε���
					{
						//�������Χ�ڣ��Ͳ���Ҫ���κεĵ���
					}
					else//����������ӵ㣬������ӵ�λ�õĵ���
					{
						adjustCameraDirection(m_viewer->getCamera(),dynamic_cast<osg::MatrixTransform*>(*myiteratorNode));//�����ӵ�
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
				//���������·���ϵĽڵ�
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

	currentcamera->getViewMatrixAsLookAt(cameraEye,toCenter,cameraUp);//��ȡ����ǰ�������λ��
	nodePos = currentnode->getMatrix().getTrans();//��ȡ��ǰmt����ҵĽڵ��λ��
	nodePos.z() = cameraEye.z();//�����ᵽͬһ��ˮƽ��������������Zֵ���

	if(((cameraEye.x()-nodePos.x())*(cameraEye.x()-nodePos.x())+(cameraEye.y()-nodePos.y())*(cameraEye.y()-nodePos.y())+(cameraEye.z()-nodePos.z())*(cameraEye.z()-nodePos.z()))>490000)//˵���뿪��Զ��
	{
		return false;//���Զ���ӵ��򷵻�false
	}
	else
	{
		return true;//��������ӵ��򷵻�true
	}
}

void CTravelManipulator::adjustCameraDirection(osg::Camera* currentcamera, osg::MatrixTransform* currentnode)
{
	osg::Vec3 cameraEye;
	osg::Vec3 toCenter;
	osg::Vec3 cameraUp;
	osg::Vec3 nodePos;

	currentcamera->getViewMatrixAsLookAt(cameraEye,toCenter,cameraUp);//��ȡ����ǰ�������λ��
	toCenter.z()=cameraEye.z();//��toCenter�������������ͳһ���ֵ�ˮƽ״̬��û��������б�ķ���
	nodePos = currentnode->getMatrix().getTrans();//��ȡ��ǰmt����ҵĽڵ��λ��

	osg::Vec3 curCameraDirection;
	osg::Vec3 tarCameraDirection;


	curCameraDirection = toCenter - cameraEye;//��ǰ��camera�ķ���
	curCameraDirection.normalize();
	osg::Vec3 nodePosToSameZ(nodePos.x(),nodePos.y(),cameraEye.z());//�����nodePos���zֵ�������͵�ǰ�����һ��ƽ�棬��ƽ��ƽ����XOYƽ��
	tarCameraDirection = nodePosToSameZ-cameraEye;//Ŀ��camera����
	tarCameraDirection.normalize();

	float fenzi=curCameraDirection.x()*tarCameraDirection.x()+curCameraDirection.y()*tarCameraDirection.y();
	float fenmu=(sqrt(curCameraDirection.x()*curCameraDirection.x()+curCameraDirection.y()*curCameraDirection.y()))*(sqrt(tarCameraDirection.x()*tarCameraDirection.x()+tarCameraDirection.y()*tarCameraDirection.y()));
	float result = fenzi/fenmu;
	float fai = acos(result);


	//����ӵ�ǰcamera��Ŀ��camera�ĵ��Ǵ�С
	if((curCameraDirection.x()*tarCameraDirection.y()-tarCameraDirection.x()*curCameraDirection.y())<0)//����������б���˳ʱ��ת��������ʱ��ת����С��0˳ʱ��
	{
		m_vRotation._v[2] -= fai;
	}
	else//����0��ʱ��
	{
		m_vRotation._v[2] += fai;
	}

	float totalDistance = sqrt((cameraEye.x()-nodePosToSameZ.x())*(cameraEye.x()-nodePosToSameZ.x())+(cameraEye.y()-nodePosToSameZ.y())*(cameraEye.y()-nodePosToSameZ.y())+(cameraEye.z()-nodePosToSameZ.z())*(cameraEye.z()-nodePosToSameZ.z()));
	float moveDistance = totalDistance - 700;

	ChangePosition(osg::Vec3 (0, moveDistance* sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
	ChangePosition(osg::Vec3 (moveDistance * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;


}*/
