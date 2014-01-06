#include <osgViewer/Viewer>
 
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
 
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
 
#include <osgUtil/Optimizer>
 
int main(){
         //����Viewer���󣬳��������
         osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
 
         //����������ڵ�
         osg::ref_ptr<osg::Group> root = new osg::Group();
 
         //����һ���ڵ㣬��ȡţ��ģ��
         osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("zhuanluntike.ive");
 
         //��ӵ�����
         root->addChild(node.get());

         //�Ż���������
         osgUtil::Optimizer optimizer;
         optimizer.optimize(root.get());
 
         //���ó�������
         viewer->setSceneData(root.get());

        //��ʼ������������
        viewer->realize();
 
         //��ʼ��Ⱦ
         viewer->run();
 
        return 0 ;
 }