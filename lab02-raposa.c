#include <stdio.h>
#include <math.h>

//função para calcular a distância de um buraco até o coelho, ou a raposa (fórmula da distância de dois pontos nem uma plano cartesiano)
float distancia(float x, float y, float xc_r, float yc_r)
{
    float distancia;
    distancia = sqrt(pow((x - xc_r), 2) + pow((y - yc_r), 2));
    return distancia;
}

int main(void)
{
    int n;
    float xcoelho, ycoelho, xraposa, yraposa, xburaco, yburaco;
    while (scanf
	   ("%d %f %f %f %f", &n, &xcoelho, &ycoelho, &xraposa,
	    &yraposa) == 5) {
	float d_raposa, d_coelho;
	int escape = 0;		//variável para verificar se o coelho pode ou não escapar, se for 0 não pode, se for 1 pode
	for (int i = 0; i < n; i++) {
	    scanf("%f %f", &xburaco, &yburaco);
	    d_raposa = distancia(xburaco, yburaco, xraposa, yraposa);	//armazena a distância da raposa até determinado buraco
	    d_coelho = distancia(xburaco, yburaco, xcoelho, ycoelho);	//armazena a distância do coelho até determinado buraco
	    if (escape == 0) {	//verifica se tem um buraco em que se possa escapar, se não tiver, não entra aqui
		if (d_raposa > (2 * d_coelho)) {	//verifica se o coelho pode escapar
		    printf
			("O coelho pode escapar pelo buraco (%.3f,%.3f).\n",
			 xburaco, yburaco);
		    escape++;	//se o coelho puder escapar muda de 0 pra 1
		}
	    }
	}
	if (escape == 0) {	//verifica se não tem nenhum buraco para escapar
	    printf("O coelho nao pode escapar.\n");
	}
    }


    return 0;
}