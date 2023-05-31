#include "linklist.h"

int main(int argc,char *argv[])
{
    link_node_t *p = CreatEpLinkList();//新建一个空结点，并用p指向

    InsetIntoPostLinkList(p,0,10);
    InsetIntoPostLinkList(p,1,20);
    InsetIntoPostLinkList(p,2,30);
    InsetIntoPostLinkList(p,3,40);
    InsetIntoPostLinkList(p,4,20);
    ShowLinkList(p);

    // InsetIntoPostLinkList(p,0,9);
    // InsetIntoPostLinkList(p,0,9);
    // ShowLinkList(p);

    // InsetIntoPostLinkList(p,2,15);
    // ShowLinkList(p);

    // InsetIntoPostLinkList(p,6,45);
    // ShowLinkList(p);

    // DeletePostLinkList(p,2);
    // ShowLinkList(p);

    // ChangePostLinkList(p,0,6);
    // ShowLinkList(p);

    // printf("%d\n",SearchDataLinkList(p,10));

    // ReverseLinkList(p);
    // ShowLinkList(p);

    // DeleteDataLinkLint(p,20);
    // ShowLinkList(p);

    ClearLinkList(p);
    ShowLinkList(p);

    free(p);
    p = NULL;
    return 0;
}