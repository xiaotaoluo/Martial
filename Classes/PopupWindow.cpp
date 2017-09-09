#include "PopupWindow.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;

PopupWindow* PopupWindow::pwInstence = new PopupWindow();

PopupWindow::PopupWindow()
{
	//初始化PopupWindow
	pw_Menu = NULL;
	pw_BackGround = NULL;
	pw_Title = NULL;
	pw_ContentText = NULL;
	m_callbackListener = NULL;
	m_callback = NULL;
	pw_Button = NULL;

	m_contentPadding = 0;
	int m_contentPaddingTop = 0;
	numBtn = 0;

	this->setContentSize(Size(0, 0));
	Menu* menu = Menu::create();
	menu->setPosition(ccp(0, 0));
	setMenuButton(menu);
	setTouchEnabled(true);


}


PopupWindow::~PopupWindow()
{
	//安全回收
	CC_SAFE_RELEASE(pw_Menu);
	CC_SAFE_RELEASE(pw_BackGround);
	CC_SAFE_RELEASE(pw_ContentText);
	CC_SAFE_RELEASE(pw_Title);
	CC_SAFE_RELEASE(pw_Button);
}

void PopupWindow::buttonCallback(Object * pSender)
{
	Node* node = dynamic_cast<Node*>(pSender);
	if (m_callback && m_callbackListener) {
		(m_callbackListener->*m_callback)(node);
		pwInstence->setVisible(false);
	}
}

void PopupWindow::ButtonEvent(Ref *pSender, cocos2d::ui::TouchEventType type)
{
	Button* btn = (Button*)pSender;
	int tag = btn->getTag();//通过Tag标签设置响应事件
	switch (tag)
	{
	case 0:
		switch (type)
		{
		case TouchEventType::TOUCH_EVENT_ENDED:
			pwInstence->setVisible(false);
			break;
		}
		break;
	case 1:
		switch (type)
		{
		case TouchEventType::TOUCH_EVENT_ENDED:
			break;
		}
		break;
	default:

		break;
	}

		
}

PopupWindow * PopupWindow::getInstance()
{
	if (pwInstence==NULL) {
		pwInstence = new PopupWindow();
	}
	//默认自适应弹窗尺寸
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	pwInstence->setContentSize(CCSizeMake(480,420));
	return pwInstence;
}

void PopupWindow::setWindowBackGround(const char * backgroundImage)
{
	pwInstence->setPopupWindowBackGround(Sprite::create(backgroundImage));
}

void PopupWindow::setWindowTitle(const char *title, const char* fontname, int fontsize) {
	pw_Title = Text::create(title,fontname, fontsize);
	pw_Title->setColor(ccc3(0,0,0));//字体颜色
	setPopupWindowTitle(pw_Title);
}

void PopupWindow::setContentText(const char * content, const char * fontname, int fontsize, int padding, int paddingTop)
{
	pw_ContentText = Label::createWithSystemFont(content,fontname, fontsize);
	pw_ContentText->setTextColor(Color4B(0, 0, 0, 250));
	setPopupWindowContentText(pw_ContentText);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

void PopupWindow::setContentTextWithTTF(const char * content, const char * fontname, int fontsize, int padding, int paddingTop)
{
	pw_ContentText = Label::createWithTTF(content, fontname, fontsize);
	pw_ContentText->setTextColor(Color4B(0, 0, 0, 255));
	setPopupWindowContentText(pw_ContentText);
	m_contentPadding = padding;
	m_contentPaddingTop = paddingTop;
}

void PopupWindow::setCallbackFunc(Object * target, SEL_CallFuncN callfun)
{
	m_callbackListener = target;
	m_callback = callfun;
}

bool PopupWindow::addMenuButton(const char * normalImage, const char * selectedImage, const char * title, const char* buttonTextFontName, int tag )
{
	Size winSize = Director::sharedDirector()->getWinSize();

	MenuItemImage* menuImage = MenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupWindow::buttonCallback));
	menuImage->setTag(tag);
	menuImage->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	Size mmenu = menuImage->getContentSize();
	Text* mttf = Text::create(title, buttonTextFontName, 16);
	mttf->setColor(ccc3(0, 0, 0));
	mttf->setPosition(ccp(mmenu.width / 2, mmenu.height / 2));
	menuImage->addChild(mttf);
	menuImage->setScale(0.3,0.3);
	getMenuButton()->addChild(menuImage);
	return true;
}

bool PopupWindow::addButton(const char * buttonImage, const char * titleText, const char * titleFontName, int titleFontSize)
{
	Size winSize = Director::sharedDirector()->getWinSize();
	auto new_Button = Button::create(buttonImage);
	new_Button->setTitleText(titleText);
	new_Button->setTitleFontName(titleFontName);
	new_Button->setTitleFontSize(titleFontSize);
	new_Button->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	Text* mttf = Text::create(titleText, titleFontName, titleFontSize);
	mttf->setColor(ccc3(0, 0, 0));
	mttf->setPosition(ccp(new_Button->getContentSize().width / 2, new_Button->getContentSize().height / 2));
	new_Button->addChild(mttf);
	new_Button->addTouchEventListener(this, toucheventselector(PopupWindow::ButtonEvent));
	pw_Button = new_Button;
	vecBtn.pushBack(new_Button);
	vecBtn.at(numBtn)->setTag(numBtn);
	numBtn++;
	return true;
}

void PopupWindow::setWindowSize(int x,int y)
{	
	pwInstence->setContentSize(CCSizeMake(x, y));

}


void PopupWindow::onEnter()
{
	Layer::onEnter();
	Size winSize = Director::sharedDirector()->getWinSize();
	Size contentSize;
	//弹窗背景
	if (getPopupWindowBackGround()) {
		pw_BackGround->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		contentSize = getPopupWindowBackGround()->getContentSize();
		float scalex = pwInstence->getContentSize().width / contentSize.width;
		float scaley = pwInstence->getContentSize().height / contentSize.height;
		pw_BackGround->setScale(scalex,scaley);

		this->addChild(pw_BackGround, 0);
		
	}
	//弹窗标题
	if (getPopupWindowTitle()) {
		pw_Title->setPosition(ccp(winSize.width / 2.0,
			winSize.height/2+ pwInstence->getContentSize().height/2.0- pw_Title->getContentSize().height/2.0-25.0));
		this->addChild(pw_Title,1);
	}

	// 弹窗内容  
	if (getPopupWindowContentText()) {
		pw_ContentText->setPosition(ccp(winSize.width / 2.0, winSize.height / 2.0));
		pw_ContentText->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
		pw_ContentText->setDimensions(pwInstence->getContentSize().width - m_contentPadding*2,
			(pwInstence->getContentSize() .height/2.0- m_contentPaddingTop- pw_Title->getContentSize().height-10)*2.0);
		this->addChild(pw_ContentText,1);
	}
	//菜单按钮
	if (getMenuButton()) {
		
		float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
		float btnHeight = pw_Menu->getContentSize().height;
		Vector<Node*> vecArray = getMenuButton()->getChildren();
		Object* pObj = NULL;
		int i = 1;
		for (auto& e : vecArray) {
			Node* node = dynamic_cast<Node*>(e);
			float scalex = pwInstence->getContentSize().width / 6 / node->getContentSize().width;
			float scaley = pwInstence->getContentSize().height / 16.4 / node->getContentSize().height;
			node->setScale(scalex, scaley);
			node->setPosition(Point(winSize.width / 2 + 100 * i,
				winSize.height / 2
				- pw_ContentText->getContentSize().height / 2 ));
			i++;
		}
		this->addChild(pw_Menu, 1);
	}
	//普通按钮
	if (getPopupWindowButton()) {
		int i = 0;
		for (auto& e : vecBtn) {
			Button* m_Button = dynamic_cast<Button*>(e);
			float scalex = pwInstence->getContentSize().width/6 / m_Button->getContentSize().width;
			float scaley = pwInstence->getContentSize().height/16.4 / m_Button->getContentSize().height;
			m_Button->setScale(scalex,scaley);
		
			m_Button->setPosition(ccp(winSize.width / 2 -100*i,winSize.height/2
				-pw_ContentText->getContentSize().height/2));
			this->addChild(m_Button, 1);
			i++;
		}
	}

}

void PopupWindow::onExit()
{
	Layer::onExit();
}

