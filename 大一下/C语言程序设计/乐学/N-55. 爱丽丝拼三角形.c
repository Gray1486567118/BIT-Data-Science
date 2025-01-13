#include <stdio.h>

int iso_tri(int a, int b, int c)
{
	if (a == b || b == c || a == c)
	{
		return 1;
	} else 
	{
		return 0;
	}
}



int rig_tri(int a, int b, int c)
{
	if (a * a + b * b == c * c)
	{
		return 1;
	} else 
	{
		return 0;
	}
}



int is_tri(int a, int b, int c)
{
	if (a + b > c)
	{
		return 1;
	} else
	{
		return 0;
	}
	
}




void triangles(int n, int l, int r)
{
	int tri = 0, iso = 0, rig = 0;
	double max_len = 1.0 * n / 3;

	int a, b, c;
	for (a = l; (a <= (int) max_len) && (a <= r); a ++)
	{
		double bc = 1.0 / 2 * (n - a);
		if (bc == (int) bc)
		{
			c = bc;
		} else
		{
			c = bc + 1;
		}
		
		for(b = bc; b >= a && c <= r && is_tri(a, b, c); b --, c ++)
		{
			tri ++;
			iso += iso_tri(a, b, c);
			rig += rig_tri(a, b, c);
		}
	}
	
	printf("%d %d %d\n", tri, iso, rig);
}




int main()
{
	int t, i, n, l, r;
	scanf("%d", &t);
	
	for (i = 0; i < t; i ++)
	{
		scanf("%d %d %d", &n, &l, &r);
		triangles(n, l, r);
	}
	return 0;
}

