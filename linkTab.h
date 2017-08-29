
#ifndef _LINK_TAB_H_
#define _LINK_TAB_H_

#include <pthread.h>
/**
 * 节点
 * next指向下一节点
 * showWay 显示链表节点数据
 */

typedef struct linknode
{
	struct linknode* next;
	void (*showWay)(void* x);

} tnode, *pnode;


/**
 * 链表
 */
typedef struct linkTab
{
	pthread_mutex_t mutex;
	pnode pHead;
	pnode pTail;
	int sum;

} tlinkTab, *plinkTab;


/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description 创建链表
 * @return		plinkTab
 */
plinkTab CreatLinkTab();

/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description 删除链表
 * @param		链表
 * @return		删除状态
 */
int DeleteLinkTab(plinkTab linkTab);

/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description 添加节点
 * @param		链表
 * @param		要添加的节点
 * @return		添加状态
 */
int AddLinkTabNode(plinkTab linkTab, void* linkNodeV);


/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description 删除节点
 * @param		链表
 * @param		要删除的节点
 * @return		删除状态
 */
int DeleteLinkTabNode(plinkTab linkTab, void* linkNode);

/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description	搜索
 * @param		链表
 * @param		搜索条件
 * @return		搜索结果
 */
void* SearchlinkTabNode(plinkTab linkTab, int condition(void* linkNode, void* aim), void* aim);


/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description	显示
 * @param		链表
 * @param		显示方式
 */
void ShowLinkTab(plinkTab linkTab);


#endif
