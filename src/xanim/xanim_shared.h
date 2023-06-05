struct XAnimTree_s;

void XAnimFreeTree(XAnimTree_s *tree, void (*Free)(void *, int));
void XAnimShutdown();
void XAnimInit();
