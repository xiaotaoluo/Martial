#ifndef __PopupWindow__  
#define __PopupWindow__  
#include "ui/CocosGUI.h"
#include "cocos2d.h"  
USING_NS_CC;
using namespace cocos2d::ui;
class PopupWindow : public  Layer
{
public:
	//��ȡΨһʵ���Ĺ�������
	static PopupWindow* getInstance();
	//���õ�������
	void setWindowBackGround(const char* backgroundImage);
	//���ñ���
	void setWindowTitle(const char* title, const char* fontname="",int fontsize=22);
	//ͨ��ϵͳ�������������ı�
	void setContentText(const char* content, const char* fontname = "", int fontsize = 18, int padding = 35, int paddingTop = 25);
	//ͨ��ttf�ļ����������ı�
	void setContentTextWithTTF(const char* content, const char* fontname, int fontsize = 16, int padding = 40, int paddingTop = 25);
	//�ص�����
	void setCallbackFunc(Object* target, SEL_CallFuncN callfun);
	//���Ӳ˵���ť
	bool addMenuButton(const char* normalImage, const char* selectedImage , const char* title, const char* buttonTextFontName = "", int tag = 0);
	//����Button
	bool addButton(const char* buttonImage, const char* titleText, const char* titleFontName="����", int titleFontSize = 25);
	//���õ����ߴ�
	void setWindowSize(int x,int y);
	virtual void onEnter();
	virtual void onExit();

private:
	PopupWindow();
	~PopupWindow();
	static PopupWindow* pwInstence;
	//��ť��Ӧ
	void buttonCallback(Object* pSender);
	//�����ı��߾�
	int m_contentPadding;
	int m_contentPaddingTop;
	//������
	Object* m_callbackListener;
	SEL_CallFuncN m_callback;
	//Button��Ӧ�¼�
	void ButtonEvent(Ref*, cocos2d::ui::TouchEventType type);
	//Button����
	int numBtn;
	//Button����
	Vector<Button*> vecBtn;
	//��ӱ�������get��set����
	CC_SYNTHESIZE_RETAIN(Menu*, pw_Menu, MenuButton);
	CC_SYNTHESIZE_RETAIN(Sprite*, pw_BackGround, PopupWindowBackGround);
	CC_SYNTHESIZE_RETAIN(Text*, pw_Title, PopupWindowTitle);
	CC_SYNTHESIZE_RETAIN(Label*, pw_ContentText, PopupWindowContentText);
	CC_SYNTHESIZE_RETAIN(Button*, pw_Button, PopupWindowButton);

};
#endif
