/**
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkTab.h"

/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description 创建链表
 * @return		plinkTab
 */
plinkTab CreatLinkTab()
{
	plinkTab linkTab = (plinkTab)malloc(sizeof(tlinkTab));
	if(linkTab == NULL)
	{
		printf("malloc error%s\n", __func__);
	}
	linkTab->pHead = NULL;
	linkTab->pTail = NULL;
	linkTab->sum = 0;
	return linkTab;
}

/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description 删除链表
 * @param		链表
 * @return		删除状态
 */
int DeleteLinkTab(plinkTab linkTab)
{
	if(linkTab == NULL)
		return -1;
	while(linkTab->pHead != NULL)
	{
		pnode p = linkTab->pHead;
		linkTab->pHead = linkTab->pHead->next;
		linkTab->sum -= 1;
		free(p);
	}
	linkTab->pHead = NULL;
	linkTab->pTail = NULL;
	linkTab->sum = 0;
	free(linkTab);
	return 0;

}

/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description 添加节点
 * @param		链表
 * @param		要添加的节点
 * @return		添加状态
 */
int AddLinkTabNode(plinkTab linkTab, void* linkNodeV)
{
	pnode linkNode = (pnode)linkNodeV;
	if(linkTab == NULL || linkNode == NULL)
	{
		return -1;
	}
	linkNode->next = NULL;
	if(linkTab->pHead == NULL)
	{
		linkTab->pHead = linkNode;
	}
	if(linkTab->pTail == NULL)
	{
		linkTab->pTail = linkNode;
	}
	else
	{
		linkTab->pTail->next = linkNode;
		linkTab->pTail = linkNode;
	}
	linkTab->sum++;
	return 0;
}


/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description 删除节点
 * @param		链表
 * @param		要删除的节点
 * @return		删除状态
 */
int DeleteLinkTabNode(plinkTab linkTab, void* linkNode)
{
	if(linkTab == NULL || linkNode == NULL)
    {
        return -1;
    }
    pthread_mutex_lock(&(linkTab->mutex));
    if(linkTab->pHead == linkNode)
    {
        linkTab->pHead = linkTab->pHead->next;
        linkTab->sum -= 1 ;
        if(linkTab->sum == 0)
        {
            linkTab->pTail = NULL;
        }
		free(linkNode);
        pthread_mutex_unlock(&(linkTab->mutex));
        return 0;
    }
    pnode pTempNode = linkTab->pHead;
    while(pTempNode != NULL)
    {
        if(pTempNode->next == linkNode)
        {
            pTempNode->next = pTempNode->next->next;
            linkTab->sum -= 1 ;
            if(linkTab->sum == 0)
            {
                linkTab->pTail = NULL;
            }
			free(linkNode);
            pthread_mutex_unlock(&(linkTab->mutex));
            return 0;
        }
        pTempNode = pTempNode->next;
    }
    pthread_mutex_unlock(&(linkTab->mutex));
    return -1;
}

/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description	搜索
 * @param		链表
 * @param		搜索条件
 * @return		搜索结果
 */
void* SearchlinkTabNode(plinkTab linkTab, int condition(void* linkNode, void* aim), void* aim)
{
	if(linkTab == NULL || condition == NULL)
		return NULL;
	pnode p = linkTab->pHead;
	while(p)
	{
		if(condition((void*)p, aim) == 1)
			return p;
		p = p->next;
	}
	return NULL;
}



/**
 * @Author      codelover
 * @DateTime    2017-05-24
 * @Description	显示
 * @param		链表
 * @param		显示方式
 */
void ShowLinkTab(plinkTab linkTab)
{

	int n = linkTab->sum;
	if(linkTab == NULL)
		return ;

	pnode p = linkTab->pHead;
	while(n--)
	{
		p->showWay(p);
		p = p->next;
	}
}
