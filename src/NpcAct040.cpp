#include "WindowsWrapper.h"

#include "NpcAct.h"

#include "MyChar.h"
#include "NpChar.h"
#include "Game.h"
#include "Caret.h"
#include "Sound.h"
#include "Back.h"
#include "Triangle.h"

//Santa
void ActNpc040(NPCHAR *npc)
{
	RECT rcLeft[7];
	RECT rcRight[7];
	
	rcLeft[0] = {0, 32, 16, 48};
	rcLeft[1] = {16, 32, 32, 48};
	rcLeft[2] = {32, 32, 48, 48};
	rcLeft[3] = {0, 32, 16, 48};
	rcLeft[4] = {48, 32, 64, 48};
	rcLeft[5] = {0, 32, 16, 48};
	rcLeft[6] = {64, 32, 80, 48};
	
	rcRight[0] = {0, 48, 16, 64};
	rcRight[1] = {16, 48, 32, 64};
	rcRight[2] = {32, 48, 48, 64};
	rcRight[3] = {0, 48, 16, 64};
	rcRight[4] = {48, 48, 64, 64};
	rcRight[5] = {0, 48, 16, 64};
	rcRight[6] = {64, 48, 80, 64};
	
	switch ( npc->act_no )
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
		case 1:
			if (Random(0, 120) == 10)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}
			if (npc->x - 0x4000 < gMC.x && npc->x + 0x4000 > gMC.x && npc->y - 0x4000 < gMC.y && npc->y + 0x2000 > gMC.y)
			{
				if (npc->x <= gMC.x)
					npc->direct = 2;
				else
					npc->direct = 0;
			}
			break;
		case 2:
			if (++npc->act_wait > 8)
			{
				npc->act_no = 1;
				npc->ani_no = 0;
			}
			break;
		case 3:
			npc->act_no = 4;
			npc->ani_no = 2;
			npc->ani_wait = 0;
		case 4:
			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				npc->ani_no++;
			}
			if (npc->ani_no > 5)
				npc->ani_no = 2;
			if (npc->direct)
				npc->x += 0x200;
			else
				npc->x -= 0x200;
			break;
		case 5:
			npc->ani_no = 6;
			break;
		default:
			break;
	}
	
	if (npc->direct)
		npc->rect = rcRight[npc->ani_no];
	else
		npc->rect = rcLeft[npc->ani_no];
}

//Busted Door
void ActNpc041(NPCHAR *npc)
{
	RECT rect[1];

	rect[0] = {0, 80, 48, 112};

	if (npc->act_no == 0)
	{
		++npc->act_no;
		npc->y -= 0x2000;	// Move a tile up
	}

	npc->rect = rect[0];
}

//Sue
void ActNpc042(NPCHAR *npc)
{
	RECT rcLeft[13];
	RECT rcRight[13];

	rcLeft[0] = {0, 0, 16, 16};
	rcLeft[1] = {16, 0, 32, 16};
	rcLeft[2] = {32, 0, 48, 16};
	rcLeft[3] = {0, 0, 16, 16};
	rcLeft[4] = {48, 0, 64, 16};
	rcLeft[5] = {0, 0, 16, 16};
	rcLeft[6] = {64, 0, 80, 16};
	rcLeft[7] = {80, 32, 96, 48};
	rcLeft[8] = {96, 32, 112, 48};
	rcLeft[9] = {128, 32, 144, 48};
	rcLeft[10] = {0, 0, 16, 16};
	rcLeft[11] = {112, 32, 128, 48};
	rcLeft[12] = {160, 32, 176, 48};

	rcRight[0] = {0, 16, 16, 32};
	rcRight[1] = {16, 16, 32, 32};
	rcRight[2] = {32, 16, 48, 32};
	rcRight[3] = {0, 16, 16, 32};
	rcRight[4] = {48, 16, 64, 32};
	rcRight[5] = {0, 16, 16, 32};
	rcRight[6] = {64, 16, 80, 32};
	rcRight[7] = {80, 48, 96, 64};
	rcRight[8] = {96, 48, 112, 64};
	rcRight[9] = {128, 48, 144, 64};
	rcRight[10] = {0, 16, 16, 32};
	rcRight[11] = {112, 48, 128, 64};
	rcRight[12] = {160, 48, 176, 64};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			npc->xm = 0;
			// Fallthrough
		case 1:
			if (Random(0, 120) == 10)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 1;
			}

			break;

		case 2:
			if (++npc->act_wait > 8)
			{
				npc->act_no = 1;
				npc->ani_no = 0;
			}

			break;

		case 3:
			npc->act_no = 4;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			// Fallthrough
		case 4:
			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 5)
				npc->ani_no = 2;

			if (npc->direct == 0)
				npc->xm = -0x200;
			else
				npc->xm = 0x200;

			break;

		case 5:
			npc->ani_no = 6;
			npc->xm = 0;
			break;

		case 6:
			PlaySoundObject(50, 1);
			npc->act_wait = 0;
			npc->act_no = 7;
			npc->ani_no = 7;
			// Fallthrough
		case 7:
			if (++npc->act_wait > 10)
				npc->act_no = 0;

			break;

		case 8:
			PlaySoundObject(50, 1);
			npc->act_wait = 0;
			npc->act_no = 9;
			npc->ani_no = 7;
			npc->ym = -0x200;

			if (npc->direct == 0)
				npc->xm = 0x400;
			else
				npc->xm = -0x400;

			// Fallthrough
		case 9:
			if (++npc->act_wait > 3 && npc->flag & 8)
			{
				npc->act_no = 10;

				if (npc->direct == 0)
					npc->direct = 2;
				else
					npc->direct = 0;
			}

			break;

		case 10:
			npc->xm = 0;
			npc->ani_no = 8;
			break;

		case 11:
			npc->act_no = 12;
			npc->act_wait = 0;
			npc->ani_no = 9;
			npc->ani_wait = 0;
			npc->xm = 0;
			// Fallthrough
		case 12:
			if (++npc->ani_wait > 8)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 10)
				npc->ani_no = 9;

			break;

		case 13:
			npc->ani_no = 11;
			npc->xm = 0;
			npc->ym = 0;
			npc->act_no = 14;

			int i;
			for (i = 0; i < 0x200 && gNPC[i].code_event != 501; ++i);

			if (i == 0x200)
			{
				npc->act_no = 0;
				break;
			}
			else
			{
				npc->pNpc = &gNPC[i];
			}
			// Fallthrough
		case 14:
			if (npc->pNpc->direct == 0)
				npc->direct = 2;
			else
				npc->direct = 0;

			if (npc->pNpc->direct == 0)
				npc->x = npc->pNpc->x - 0xC00;
			else
				npc->x = npc->pNpc->x + 0xC00;

			npc->y = npc->pNpc->y + 0x800;

			if (npc->pNpc->ani_no == 2 || npc->pNpc->ani_no == 4)
				npc->y -= 0x200;

			break;

		case 15:
			npc->act_no = 16;
			SetNpChar(257, npc->x + 0x10000, npc->y, 0, 0, 0, 0, 0);
			SetNpChar(257, npc->x + 0x10000, npc->y, 0, 0, 2, 0, 0x80);
			npc->xm = 0;
			npc->ani_no = 0;
			// Fallthrough
		case 16:
			gSuperXpos = npc->x - 0x3000;
			gSuperYpos = npc->y - 0x1000;
			break;

		case 17:
			npc->xm = 0;
			npc->ani_no = 12;
			gSuperXpos = npc->x;
			gSuperYpos = npc->y - 0x1000;
			break;

		case 20:
			npc->act_no = 21;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			// Fallthrough
		case 21:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 5)
				npc->ani_no = 2;

			if (npc->direct == 0)
				npc->xm = -0x400;
			else
				npc->xm = 0x400;

			if (npc->x < gMC.x - 0x1000)
			{
				npc->direct = 2;
				npc->act_no = 0;
			}

			break;

		case 30:
			npc->act_no = 31;
			npc->ani_no = 2;
			npc->ani_wait = 0;
			// Fallthrough
		case 31:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 5)
				npc->ani_no = 2;

			if (npc->direct == 0)
				npc->xm = -0x400;
			else
				npc->xm = 0x400;

			break;

		case 40:
			npc->act_no = 41;
			npc->ani_no = 9;
			npc->ym = -0x400;
			break;
	}

	if (npc->act_no != 14)
	{
		npc->ym += 0x40;

		if (npc->xm > 0x400)
			npc->xm = 0x400;
		if (npc->xm < -0x400)
			npc->xm = -0x400;

		if (npc->ym > 0x5FF)
			npc->ym = 0x5FF;

		npc->x += npc->xm;
		npc->y += npc->ym;
	}

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}

//Chalkboard
void ActNpc043(NPCHAR *npc)
{
	RECT rcLeft[1];
	RECT rcRight[1];

	rcLeft[0] = {128, 80, 168, 112};
	rcRight[0] = {168, 80, 208, 112};

	if (npc->act_no == 0)
	{
		npc->act_no = 1;
		npc->y -= 0x2000;
	}

	if (npc->direct == 0)
		npc->rect = rcLeft[0];
	else
		npc->rect = rcRight[0];
}

//H/V Trigger
void ActNpc046(NPCHAR *npc)
{
	RECT rect[1];
	rect[0] = {0, 0, 16, 16};

	npc->bits |= 0x100;

	if (npc->direct == 0)
	{
		if (npc->x >= gMC.x)
			npc->x -= 0x5FF;
		else
			npc->x += 0x5FF;
	}
	else
	{
		if (npc->y >= gMC.y)
			npc->y -= 0x5FF;
		else
			npc->y += 0x5FF;
	}

	npc->rect = rect[0];
}

//Omega projectiles
void ActNpc048(NPCHAR *npc)
{
	if (npc->flag & 1 && npc->xm < 0)
	{
		npc->xm = -npc->xm;
	}
	else if (npc->flag & 4 && npc->xm > 0)
	{
		npc->xm = -npc->xm;
	}
	else if (npc->flag & 8)
	{
		if (++npc->count1 <= 2 && npc->direct != 2)
		{
			npc->ym = -0x100;
		}
		else
		{
			VanishNpChar(npc);
			SetCaret(npc->x, npc->y, 2, 0);
		}
	}
	
	if (npc->direct == 2)
	{
		npc->bits &= ~npc_shootable;
		npc->bits |= npc_invulnerable;
	}
	
	npc->ym += 5;
	npc->y += npc->ym;
	npc->x += npc->xm;
	
	RECT rcLeft[2];
	RECT rcRight[2];
	rcLeft[0] = {288, 88, 304, 104};
	rcLeft[1] = {304, 88, 320, 104};
	rcRight[0] = {288, 104, 304, 120};
	rcRight[1] = {304, 104, 320, 120};
	
	if (++npc->ani_wait > 2)
	{
		npc->ani_wait = 0;
		if (++npc->ani_no > 1)
			npc->ani_no = 0;
	}
	
	if (++npc->act_wait > 750)
	{
		SetCaret(npc->x, npc->y, 2, 0);
		npc->cond = 0;
	}
	
	if (npc->direct)
		npc->rect = rcRight[npc->ani_no];
	else
		npc->rect = rcLeft[npc->ani_no];
}

//Cairn
void ActNpc055(NPCHAR *npc)
{
	RECT rcLeft[6];
	RECT rcRight[6];

	rcLeft[0] = {192, 192, 208, 216};
	rcLeft[1] = {208, 192, 224, 216};
	rcLeft[2] = {192, 192, 208, 216};
	rcLeft[3] = {224, 192, 240, 216};
	rcLeft[4] = {192, 192, 208, 216};
	rcLeft[5] = {240, 192, 256, 216};

	rcRight[0] = {192, 216, 208, 240};
	rcRight[1] = {208, 216, 224, 240};
	rcRight[2] = {192, 216, 208, 240};
	rcRight[3] = {224, 216, 240, 240};
	rcRight[4] = {192, 216, 208, 240};
	rcRight[5] = {240, 216, 256, 240};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			npc->ani_no = 0;
			npc->ani_wait = 0;
			break;

		case 3:
			npc->act_no = 4;
			npc->ani_no = 1;
			npc->ani_wait = 0;
			// Fallthrough
		case 4:
			if (++npc->ani_wait > 4)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 4)
				npc->ani_no = 1;

			if (npc->direct == 0)
				npc->x -= 0x200;
			else
				npc->x += 0x200;

			break;

		case 5:
			npc->ani_no = 5;
			break;
	}

	npc->ym += 0x20;
	if (npc->ym > 0x5FF)
		npc->ym = 0x5FF;

	npc->y += npc->ym;

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}

//Beetle (Sand Zone)
void ActNpc056(NPCHAR *npc)
{
	RECT rcLeft[3];
	RECT rcRight[3];

	rcLeft[0] = {0, 144, 16, 160};
	rcLeft[1] = {16, 144, 32, 160};
	rcLeft[2] = {32, 144, 48, 160};

	rcRight[0] = {0, 160, 16, 176};
	rcRight[1] = {16, 160, 32, 176};
	rcRight[2] = {32, 160, 48, 176};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;

			if (npc->direct == 0)
				npc->act_no = 1;
			else
				npc->act_no = 3;

			break;

		case 1:
			npc->xm -= 0x10;

			if (npc->xm < -0x400)
				npc->xm = -0x400u;

			if (npc->shock)
				npc->x += npc->xm / 2;
			else
				npc->x += npc->xm;

			if (++npc->ani_wait > 1)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 2)
				npc->ani_no = 1;

			if (npc->flag & 1)
			{
				npc->act_no = 2;
				npc->act_wait = 0;
				npc->ani_no = 0;
				npc->xm = 0;
				npc->direct = 2;
			}

			break;

		case 2:
			if (npc->x < gMC.x && npc->x > gMC.x - 0x20000 && npc->y < gMC.y + 0x1000 && npc->y > gMC.y - 0x1000)
			{
				npc->act_no = 3;
				npc->ani_wait = 0;
				npc->ani_no = 1;
			}

			break;

		case 3:
			npc->xm += 0x10;

			if (npc->xm > 0x400)
				npc->xm = 0x400;

			if (npc->shock)
				npc->x += npc->xm / 2;
			else
				npc->x += npc->xm;

			if (++npc->ani_wait > 1)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 2)
				npc->ani_no = 1;

			if (npc->flag & 4)
			{
				npc->act_no = 4;
				npc->act_wait = 0;
				npc->ani_no = 0;
				npc->xm = 0;
				npc->direct = 0;
			}

			break;

		case 4:
			if (npc->x < gMC.x + 0x20000 && npc->x > gMC.x && npc->y < gMC.y + 0x1000 && npc->y > gMC.y - 0x1000)
			{
				npc->act_no = 1;
				npc->ani_wait = 0;
				npc->ani_no = 1;
			}

			break;
	}

	if (npc->direct == 0)
		npc->rect = rcLeft[npc->ani_no];
	else
		npc->rect = rcRight[npc->ani_no];
}

//Basu (Egg Corridor)
void ActNpc058(NPCHAR *npc)
{
	RECT rcLeft[3];
	RECT rcRight[3];

	rcLeft[0] = {192, 0, 216, 24};
	rcLeft[1] = {216, 0, 240, 24};
	rcLeft[2] = {240, 0, 264, 24};

	rcRight[0] = {192, 24, 216, 48};
	rcRight[1] = {216, 24, 240, 48};
	rcRight[2] = {240, 24, 264, 48};

	switch (npc->act_no)
	{
		case 0:
			if ( gMC.x >= npc->x + 0x2000 || gMC.x <= npc->x - 0x2000 )
			{
				npc->rect.right = 0;
				npc->damage = 0;
				npc->xm = 0;
				npc->ym = 0;
				npc->bits &= ~0x20;
			}
			else
			{
				npc->bits |= 0x20;
				npc->ym = -0x100;
				npc->tgt_x = npc->x;
				npc->tgt_y = npc->y;
				npc->act_no = 1;
				npc->act_wait = 0;
				npc->count1 = npc->direct;
				npc->count2 = 0;
				npc->damage = 6;

				if (npc->direct == 0)
				{
					npc->x = gMC.x + 0x20000;
					npc->xm = -0x2FFu;
				}
				else
				{
					npc->x = gMC.x - 0x20000;
					npc->xm = 0x2FF;
				}
			}

			break;

		case 1:
			if (npc->x <= gMC.x)
			{
				npc->direct = 2;
				npc->xm += 0x10;
			}
			else
			{
				npc->direct = 0;
				npc->xm -= 0x10;
			}

			if (npc->flag & 1)
				npc->xm = 0x200;

			if (npc->flag & 4)
				npc->xm = -0x200;

			if (npc->y >= npc->tgt_y)
				npc->ym -= 8;
			else
				npc->ym += 8;

			if (npc->xm > 0x2FF)
				npc->xm = 0x2FF;
			if (npc->xm < -0x2FF)
				npc->xm = -0x2FF;

			if (npc->ym > 0x100)
				npc->ym = 0x100;
			if (npc->ym < -0x100)
				npc->ym = -0x100;

			if (npc->shock)
			{
				npc->x += npc->xm / 2;
				npc->y += npc->ym / 2;
			}
			else
			{
				npc->x += npc->xm;
				npc->y += npc->ym;
			}

			if (gMC.x > npc->x + 0x32000 || gMC.x < npc->x - 0x32000)	// TODO: Maybe do something about this for widescreen
			{
				npc->act_no = 0;
				npc->xm = 0;
				npc->direct = npc->count1;
				npc->x = npc->tgt_x;
				npc->rect.right = 0;
				npc->damage = 0;
				break;
			}

			// Fallthrough
		case 2:
			if (npc->act_no)
			{
				if (npc->act_wait < 150)
					++npc->act_wait;

				if (npc->act_wait == 150)
				{
					if ((++npc->count2 % 8) == 0 && npc->x < gMC.x + 0x14000 && npc->x > gMC.x - 0x14000)	// TODO: Maybe do something about this for tallscreen
					{
						unsigned char deg = GetArktan(npc->x - gMC.x, npc->y - gMC.y);
						unsigned char rand_deg = Random(-6, 6) + deg;
						int ym = 2 * GetSin(rand_deg);
						int xm = 2 * GetCos(rand_deg);
						SetNpChar(84, npc->x, npc->y, xm, ym, 0, 0, 0x100);
						PlaySoundObject(39, 1);
					}

					if (npc->count2 > 8)
					{
						npc->act_wait = 0;
						npc->count2 = 0;
					}
				}
			}

			if (++npc->ani_wait > 1)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no > 1)
				npc->ani_no = 0;

			if (npc->act_wait > 120 && npc->act_wait / 2 % 2 == 1 && npc->ani_no == 1)
				npc->ani_no = 2;

			if (npc->direct == 0)
				npc->rect = rcLeft[npc->ani_no];
			else
				npc->rect = rcRight[npc->ani_no];

			break;
	}
}

//Eye door
void ActNpc059(NPCHAR *npc)
{
	RECT rcLeft[4];

	rcLeft[0] = {224, 16, 240, 40};
	rcLeft[1] = {208, 80, 224, 104};
	rcLeft[2] = {224, 80, 240, 104};
	rcLeft[3] = {240, 80, 256, 104};

	switch (npc->act_no)
	{
		case 0:
			npc->act_no = 1;
			// Fallthrough

		case 1:
			if (npc->x - 0x8000 < gMC.x && npc->x + 0x8000 > gMC.x && npc->y - 0x8000 < gMC.y && npc->y + 0x8000 > gMC.y)
			{
				npc->act_no = 2;
				npc->ani_wait = 0;
			}

			break;

		case 2:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				++npc->ani_no;
			}

			if (npc->ani_no == 2)
				npc->act_no = 3;

			break;

		case 3:
			if (npc->x - 0x8000 >= gMC.x || npc->x + 0x8000 <= gMC.x || npc->y - 0x8000 >= gMC.y || npc->y + 0x8000 <= gMC.y)
			{
				npc->act_no = 4;
				npc->ani_wait = 0;
			}

			break;

		case 4:
			if (++npc->ani_wait > 2)
			{
				npc->ani_wait = 0;
				--npc->ani_no;
			}

			if (npc->ani_no == 0)
				npc->act_no = 1;

			break;
	}

	if (npc->shock)
		npc->rect = rcLeft[3];
	else
		npc->rect = rcLeft[npc->ani_no];
}
