#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Element; // 배열의 원소 타입

typedef struct _Array // 배열 구조체 정의
{
    Element *elements;
    int num_of_elements;
    int length;
} Array;

Array *CreateArray(int length) // 배열 생성
{
    if (length < 1)
        return NULL;

    Array *array = malloc(sizeof *array);

    if (array == NULL) 
        return NULL;

    array->elements = malloc(length * sizeof *(array->elements));

    if (array->elements == NULL) 
        return NULL;
    
    array->num_of_elements = 0;
    array->length = length;

    return array;
}

int GetElement(Array *array, int idx, Element *element_ptr) // 인덱스로 원소 접근
{
    if (array == NULL || idx >= array->num_of_elements || idx < 0)
        return FALSE;
    
    *element_ptr = array->elements[idx];
    
    return TRUE; 
}

int SetElement(Array *array, int idx, Element element) // 인덱스의 원소 변경
{
    if (array == NULL || idx >= array->num_of_elements || idx < 0)
        return FALSE;
    
    array->elements[idx] = element;

    return TRUE;
}

int Insert(Array *array, int idx, Element element) // 인덱스에 원소 삽입
{
    if (array == NULL || idx > array->num_of_elements || idx < 0 || array->length == array->num_of_elements)
        return FALSE;
    
    for (int i = array->num_of_elements; i > idx; i--)
        array->elements[i] = array->elements[i - 1];
    array->elements[idx] = element;
    (array->num_of_elements)++;

    return TRUE;
}

int Delete(Array *array, int idx) // 인덱스의 원소 삭제
{
    if (array == NULL || idx >= array->num_of_elements || idx < 0)
        return FALSE;
    
    for (int i = idx; i < array->num_of_elements - 1; i++)
        array->elements[i] = array->elements[i + 1];
    (array->num_of_elements)--;

    return TRUE;
}

int Traverse(Array *array) // 배열의 모든 원소 출력
{
    if (array == NULL || array->num_of_elements == 0)
        return FALSE;
    
    for (int i = 0; i < array->num_of_elements; i++)
        printf("%d ", array->elements[i]);
    printf("\n");

    return TRUE;
}