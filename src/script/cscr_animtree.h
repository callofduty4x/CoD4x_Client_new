#include <q_shared.h>

struct scr_animtree_t
{
  struct XAnim_s *anims;
};

struct scrAnimPub_t
{
  unsigned int animtrees;
  unsigned int animtree_node;
  unsigned int animTreeNames;
  struct scr_animtree_t xanim_lookup[2][128];
  unsigned int xanim_num[2];
  unsigned int animTreeIndex;
  bool animtree_loading;
};

struct scr_anim_s
{
	union{
		struct{
			uint16_t index;
 			uint16_t tree;
		};
		const char *linkPointer;
	};
};

extern struct scrAnimPub_t gScrAnimPub;
struct XAnim_s* Scr_GetAnims(unsigned int index);
const char* XAnimGetAnimDebugName(const XAnim_s *anims, unsigned int animIndex); //Maybe wrong place
void Scr_UsingTree(const char *filename, unsigned int sourcePos);
void SetAnimCheck(int bAnimCheck);
