#include "HUD.h"


HUD::HUD(void)
{
	text = new osgText::Text();
}


HUD::~HUD(void)
{
}

osg::ref_ptr<osg::Camera> HUD::createHUDText(){
	osg::ref_ptr<osg::Camera>camera = new osg::Camera();

	camera->setProjectionMatrix(osg::Matrix::ortho2D(0, 1280, 0,800));
	camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	camera->setViewMatrix(osg::Matrix::identity());
	camera->setClearMask(GL_DEPTH_BUFFER_BIT);
	camera->setRenderOrder(osg::Camera::POST_RENDER);

	//camera->setAllowEventFocus(false);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::StateSet> stateset = geode->getOrCreateStateSet();

	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);

	//osg::ref_ptr<osgText::Text> text = new osgText::Text();
	osg::ref_ptr<osgText::Font> font = new osgText::Font();
	font = osgText::readFontFile("simhei.ttf");

	text->setFont(font.get());
	text->setText("");
	text->setPosition(osg::Vec3(0.0f, 750.0f, 0.0f));
	text->setCharacterSize(15.0f);
	text->setColor(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	text->setDrawMode(osgText::Text::TEXT | osgText::Text::BOUNDINGBOX);
	text->setDataVariance(osg::Object::DYNAMIC);

	geode->addDrawable(text.get());
	camera->addChild(geode.get());
	return camera.get();
}
