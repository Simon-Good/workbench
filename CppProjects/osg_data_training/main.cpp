#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/MatrixTransform>

#include <osgManipulator/Selection>
#include <osgManipulator/CommandManager>
#include <osgManipulator/TranslateAxisDragger>
#include "PickModelHandler.h"
#include <osg/ValueObject>
 
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
 
#include <osgUtil/Optimizer>

#include <string>
#include "ImageHandler.h"
#include "TravelManipulator.h"

#include "HUD.h"
#include "MouseHandler.h"

 
int main(){
         //����Viewer���󣬳��������
         osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
		 viewer->setCameraManipulator(new CTravelManipulator(viewer));
		// bool b;
 
         //����������ڵ�
         osg::ref_ptr<osg::Group> root = new osg::Group();
		 root->setName("root");
 
         osg::ref_ptr<osg::Node> platFormNd = osgDB::readNodeFile("platform.3ds");
		 platFormNd->setName("platform");
		 //osg::ref_ptr<osg::MatrixTransform> platFormMTr = new osg::MatrixTransform();
		 osg::ref_ptr<osgManipulator::Selection> platFormSEL = new osgManipulator::Selection;
		 platFormSEL->addChild(platFormNd.get());

		 osg::ref_ptr<osg::Node> pingTaiNd = osgDB::readNodeFile("pingtaihezhou.3ds");
		 pingTaiNd->setName("pingtaihezhou");
		 //osg::ref_ptr<osg::MatrixTransform> pingTaiMTr = new osg::MatrixTransform();
		 osg::ref_ptr<osgManipulator::Selection> pingTaiSEL = new osgManipulator::Selection;
		 osg::Matrix m1;
		 m1.makeTranslate(osg::Vec3(0.0f, 0.0f, 10.0f));
		 pingTaiSEL->setMatrix(m1);
		 pingTaiSEL->addChild(pingTaiNd.get());

		 osg::ref_ptr<osg::Node> chilun1Nd = osgDB::readNodeFile("chilun1.3ds");
		 chilun1Nd->setName("chilun1");
		 osg::ref_ptr<osgManipulator::Selection> chilun1SEL = new osgManipulator::Selection;//selection����Ҳ��matrix������
		 chilun1SEL->setName("chilun1SEL");
		 osg::Matrix m2;
		 m2.makeTranslate(osg::Vec3(-85.0f, -43.0f, 5.0f));
		 chilun1SEL->setMatrix(m2);
		 chilun1SEL->addChild(chilun1Nd.get());

	     /*osg::ref_ptr<osgManipulator::CommandManager>manager = new osgManipulator::CommandManager;
		 osg::ref_ptr<osgManipulator::Selection>selection = new osgManipulator::Selection;
		 osg::ref_ptr<osgManipulator::TranslateAxisDragger>dragger=new osgManipulator::TranslateAxisDragger();
		 selection->addChild(chilun1Nd.get());
		 selection->setMatrix(osg::Matrix::translate(-85.0f, 0.0f, 5.0f));
		 float scale=chilun1Nd->getBound().radius()*1.2;
		 dragger->setupDefaultGeometry();
		 dragger->setMatrix(osg::Matrix::scale(scale,scale,scale)*
							osg::Matrix::translate(selection->getBound().center()));

		 root->addChild(dragger.get());
		 root->addChild(selection.get());
		 manager->connect(*dragger,*selection);*/

		 osg::ref_ptr<osg::Node> chilun2Nd = osgDB::readNodeFile("chilun2.3ds");
		 chilun2Nd->setName("chilun2");
		 //osg::ref_ptr<osg::MatrixTransform> chilun2MTr = new osg::MatrixTransform();
		 osg::ref_ptr<osgManipulator::Selection>chilun2SEL = new osgManipulator::Selection;
		 osg::Matrix m3;
		 m3.makeTranslate(osg::Vec3(-85.0f, 32.0f, 5.0f));
		 chilun2SEL->setMatrix(m3);
		 chilun2SEL->addChild(chilun2Nd.get());

 
         //��ӵ�����
         root->addChild(platFormSEL.get());
		 root->addChild(pingTaiSEL.get());
		 root->addChild(chilun1SEL.get());
		 root->addChild(chilun2SEL.get());

         //�Ż���������
         osgUtil::Optimizer optimizer;
         optimizer.optimize(root.get());
		 
		 HUD *hud = new HUD();
		 CMouseHandler *mh = new CMouseHandler(hud->text);
		 root->addChild(hud->createHUDText());
		 viewer->addEventHandler(mh);
 
         //���ó�������
		 ImageHandler *ih = new ImageHandler();
		 viewer->getCamera()->attach(osg::Camera::COLOR_BUFFER, ih->image_c.get());
		 viewer->addEventHandler(ih);
		 viewer->addEventHandler(new PickModelHandler(root));
         viewer->setSceneData(root.get());

        //��ʼ������������
        viewer->realize();
 
         //��ʼ��Ⱦ
         viewer->run();
 
        return 0 ;
 }