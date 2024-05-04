/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "sdb.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() 
{
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp()
{
  WP* new;
  WP* temp;
  if(free_ == NULL)
  {
    printf("all watchpoints are used!");
    assert(0);
  }
  else 
  {
    new = free_;
    free_ = free_->next;  
    new->next = NULL;
    printf(" %d \n",new->NO);
  }
  
  if(head == NULL)
  {
    head = new;  
    head->next = NULL;
  }
  else 
  {
    temp = head;
    while(temp->next != NULL)
      temp = temp->next;
    temp->next = new;
  }
  return new;

}

void free_wp(WP*wp)
{
  WP* temp = free_;
  WP* temp1 = head;
  //delete from work
  if(head->NO == wp->NO)
  {
    head= wp->next;
  }
  else 
  {
  while(temp1->next->NO != wp->NO)
  {
    temp1 = temp1->next;
  }
    temp1->next = wp->next;
  }
  //insert to free
  if(wp->NO < temp->NO)
  { 
    wp->next = free_;
    free_ = wp->next;
  }
  else 
  {
  while(temp->next != NULL)
  {
    if(temp->NO<wp->NO && temp->next->NO>wp->NO)  
    {
      wp->next = temp->next;
      temp->next = wp;
      break;
    }
    temp = temp->next;
  }
  if(temp->next ==NULL)
  {
    temp->next = wp;
    wp->next = NULL;
  }
  }
}

int Wp_info(void)
{
  WP*temp;
  if(head == NULL)
  {
    printf("no watchpoints \n");
    return 0;
  }
  temp = head;
  while(temp->next !=  NULL)
  {
    printf("watchpoint%d: exp->%s val-> %d",temp->NO,temp->exp,temp->value);
    temp = temp->next;
  }
  printf("watchpoint%d: exp->%s val-> %d",temp->NO,temp->exp,temp->value);
  return 0;
}
