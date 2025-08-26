#include <stdio.h>


int main(void)
{
    int x, y, x1, y1, x2, y2, n;
    int teste = 1;

    while (1) {
	int meteoros = 0;
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);	//lê as coordeanadas da fazenda
	if (x1 != 0 && x2 != 0 && y1 != 0 && y2 != 0) {	//se for todas iguais a zero para o programaa
	    scanf("%d", &n);
	    for (int i = 0; i < n; i++) {
		scanf("%d %d", &x, &y);
		if ((x >= x1 && x <= x2) && (y <= y1 && y >= y2)) {	//verifica se os meteoros estão da área da fazenda e se estiver acrescenta 1
		    meteoros++;
		}
	    }
	    printf("Teste %d\n", teste);
	    printf("%d\n", meteoros);
	    printf("\n");
	} else {
	    break;
	}
	teste++;
    }
    return 0;
}

