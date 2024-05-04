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

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char exp[32];
  
} WP;

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
    new->next = NULL;
    free_ = free_->next;
  }
  
  if(head == NULL)
  {
    head = new;  
  }
  else 
  {
    temp = head;
    while(temp->next == NULL)
      temp = temp->next;
  }
  return new;

}

void free_wp(WP*wp)
{
  WP* temp = free_;
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