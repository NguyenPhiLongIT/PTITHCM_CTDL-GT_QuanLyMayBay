#ifndef __PASSENGER__UTILS__
#define __PASSENGER__UTILS__

#include <string.h>
#include "types.h"

//Khoi tao danh sach hanh khach
void InitTreePass(TreePass &rootPass)
{
	rootPass = NULL;
}

//Kiem tra danh sach trong
bool EmptyPass(TreePass &rootPass)
{
	return rootPass == NULL;
}

//Tao 1 hanh khach moi
PPassNode NewPassNode(Passenger &data)
{
	PPassNode passNode = new PassNode;
	passNode->data = data;
	passNode->pLeft = passNode->pRight = NULL;
	return passNode;
}

//So luong hanh khach
int countPass(TreePass &rootPass)
{
	if(rootPass == NULL)	return 0;

	return 1 + countPass(rootPass->pLeft) + countPass(rootPass->pRight);
}

//Them hanh khach vao danh sach
void InsertPass(TreePass &rootPass, Passenger &pass)
{
	if (EmptyPass(rootPass))
	{
		rootPass = NewPassNode(pass);
		return;
	}

	if (pass.id > rootPass->data.id)
        InsertPass(rootPass->pRight, pass);
    else InsertPass(rootPass->pLeft, pass);
}

//Tim kiem hanh khach
PPassNode SearchPass(TreePass rootPass, int idPass)
{
	if(rootPass == NULL) return NULL;
	if(idPass == rootPass->data.id)	return rootPass;
	if (idPass > rootPass->data.id)
        return SearchPass(rootPass->pRight, idPass);
    return SearchPass(rootPass->pLeft, idPass);
}

//Giai phong cay
void DeleteAllTreePass(TreePass &rootPass){
	if(rootPass == NULL){
		return;
	}
	DeleteAllTreePass(rootPass->pLeft);
	DeleteAllTreePass(rootPass->pRight);
	delete rootPass;
	rootPass = NULL;
}

#endif
