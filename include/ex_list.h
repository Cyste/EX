/*
	Copyright 2015 Mariusz Dzikowski

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#ifndef EX_LIST_H_
#define EX_LIST_H_

typedef struct ex_list_node {
	struct ex_list_node* next;
	struct ex_list_node* prev;
} ex_list_node;

typedef struct ex_list {
	ex_list_node sentinel;
} ex_list;

EX_API ex_list_node* ex_list_insert(ex_list_node* list_node, void* object);

EX_API void* ex_list_remove(ex_list_node* list_node);

#define ex_list_begin(list) ((list) -> sentinel.next)
#define ex_list_end(list)   (& (list) -> sentinel)

#define ex_list_is_empty(list) (ex_list_begin(list) == ex_list_end(list))

#define ex_list_next(iterator) ((iterator) -> next)
#define ex_list_previous(iterator) ((iterator) -> previous)

#define ex_list_front(list) ((void *) (list) -> sentinel.next)
#define ex_list_back(list) ((void *) (list) -> sentinel.previous)

#endif