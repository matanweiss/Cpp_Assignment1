#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct AdptArray_
{
    PElement *arr;
    size_t size;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC c, DEL_FUNC d, PRINT_FUNC p)
{
    PAdptArray adptArray = (PAdptArray)malloc(sizeof(struct AdptArray_));
    if (!adptArray)
        return FAIL;
    adptArray->arr = (PElement *)malloc(sizeof(PElement) * 2);
    adptArray->arr[0] = NULL;
    adptArray->arr[1] = NULL;
    if (!adptArray->arr)
    {
        free(adptArray);
        return FAIL;
    }
    adptArray->size = 2;
    adptArray->copyFunc = c;
    adptArray->delFunc = d;
    adptArray->printFunc = p;
    return adptArray;
}

void DeleteAdptArray(PAdptArray adptArray)
{
    for (size_t i = 0; i < adptArray->size; i++)
    {
        PElement element = adptArray->arr[i];
        if (element)
            adptArray->delFunc(element);
    }
    free(adptArray->arr);
    free(adptArray);
}

Result SetAdptArrayAt(PAdptArray adptArray, int index, PElement element)
{
    if (index < adptArray->size)
    {
        PElement oldElement = adptArray->arr[index];
        if (oldElement)
        {
            adptArray->delFunc(oldElement);
        }
        adptArray->arr[index] = adptArray->copyFunc(element);
    }
    else
    {
        adptArray->arr = (PElement *)realloc(adptArray->arr, sizeof(PElement) * (index + 1));
        if (!adptArray->arr)
            return FAIL;
        for (size_t i = adptArray->size; i < index + 1; i++)
        {
            adptArray->arr[i] = NULL;
        }
        adptArray->size = index + 1;
        adptArray->arr[index] = adptArray->copyFunc(element);
    }
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray adptArray, int index)
{
    if (adptArray->size <= index)
        return NULL;
    else if (adptArray->arr[index] == NULL)
        return NULL;
    else
        return adptArray->copyFunc(adptArray->arr[index]);
}

int GetAdptArraySize(PAdptArray adptArray)
{
    return adptArray->size;
}

void PrintDB(PAdptArray adptArray)
{
    for (size_t i = 0; i < adptArray->size; i++)
    {
        if (adptArray->arr[i])
            adptArray->printFunc(adptArray->arr[i]);
    }
}
