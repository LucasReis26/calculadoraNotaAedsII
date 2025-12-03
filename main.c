#include <stdio.h>
#include <stdlib.h>

typedef struct Prova{
	float provaPratica;
	float provaTeorica;
	float quiz;
	float total;
}Prova;

void leProva(Prova*);
int* procuraMaiores(Prova*);
float calculaFQ(Prova*);
float calculaDesempenho(Prova*,float);

int main(){

	Prova p[3];
	float tps;
	float ada;
	float desempenho;
	float notaTotal;

	printf("Calculadora de Nota AEDs-II\n");
	printf("===========================\n");

	for(int i = 0; i < 3; i++){
		printf("\nInsira as notas da prova %d\n",i + 1);
		printf("---------------------------\n");
		leProva(&p[i]);
	}

	do{
		printf("\nDigite sua nota nos TPs (0-20): ");
		scanf("%f",&tps);
		if(tps < 0 || tps > 20) printf("ERRO: Nota de TP incorreta.\n");
	}while(tps < 0 || tps > 20);

	desempenho = calculaDesempenho(p,tps);

	do{
		printf("\nDigite quanto você tirou na ADA (0-5): ");
		scanf("%f",&ada);
		if(ada < 0 || ada > 5) printf("ERRO: Nota da ADA incorreta.\n");
	}while(ada < 0 || ada > 5);


	printf("\nSuas notas\n");
	printf("---------------------------\n");
	printf("Nota da P1: %.2f\n",p[0].total);
	printf("Nota da P2: %.2f\n",p[1].total);
	printf("Nota da P3: %.2f\n",p[2].total);
	printf("Nota dos TPs: %.2f\n",tps);
	printf("Nota do Desempenho: %.2f\n",desempenho);
	printf("Nota da ADA: %.2f\n",ada);
	printf("---------------------------\n");
	
	notaTotal = p[0].total + p[1].total + p[2].total + tps + ada + desempenho;

	printf("\nSua nota total de AEDs-II: %.2f\n",notaTotal);
	if(notaTotal < 60){
		printf("Nota pendente: %.2f\n",(notaTotal - 60.0) * -1);
	}else{
		printf("Você foi aprovado!\n");
	}

	return 0;
}

void leProva(Prova* p){
	do{
		printf("\nDigite o valor da prova teorica (0-10): ");
		scanf("%f",&p->provaTeorica);
		if(p->provaTeorica < 0 || p->provaTeorica > 10) printf("ERRO: Nota da teorica incorreta\n");
	}while(p->provaTeorica < 0 || p->provaTeorica > 10);
	do{
		printf("Digite o valor da prova pratica (0-8): ");
		scanf("%f",&p->provaPratica);
		if(p->provaPratica < 0 || p->provaPratica > 8) printf("ERRO: Nota da pratica incorreta\n");
	}while(p->provaPratica < 0 || p->provaPratica > 8);
	do{
		printf("Digite o valor do quiz (0-2): ");
		scanf("%f",&p->quiz);
		if(p->quiz < 0 || p->quiz > 2) printf("ERRO: Nota de quiz incorreta\n");
	}while(p->quiz < 0 || p->quiz > 2);

	//Calcula nota total da prova.
	p->total = p->provaPratica + p->provaTeorica + p->quiz;

	return; 
}

int* procuraMaiores(Prova* p){
	int* resp = (int*)malloc(sizeof(int));

	int indicesProvas[3] = {0,1,2};

	//Ordena indices das maiores provas e retorna.
	for(int i = 0; i < 2; i++){
		int maior = i;
		for(int j = i + 1; j < 3; j++){
			if(p[maior].total < p[j].total){
				maior = j;
			}
		}
		int tmp = indicesProvas[maior];
		indicesProvas[maior] = indicesProvas[i];
		indicesProvas[i] = tmp;
	}

	resp[0] = indicesProvas[0];
	resp[1] = indicesProvas[1];

	return resp;
}

float calculaDesempenho(Prova* p, float tps){
	float resp;

	int* maioresProvas = procuraMaiores(p);

	float desempenhoProvas = (p[maioresProvas[0]].total + p[maioresProvas[1]].total) / 40;

	float desempenhoTps = tps / 20;

	float fatorQuiz = calculaFQ(p);

	//Fórmula de calculo do desempenho (duasMaioresProvas/40) * (tps/20) * fatorQuiz * 15
	resp = desempenhoProvas * desempenhoTps * fatorQuiz * 15;

	return resp;
}

float calculaFQ(Prova* p){
	float resp;

	//Calcula porcentagem dos quizzes
	resp = (p[0].quiz +p[1].quiz +p[2].quiz) / 6;

	//Multiplicando por 0.3 de acordo com a formula.
	resp *= 0.3;

	//Adicionando 1 de acordo com a fórmula.
	resp++;

	return resp;
}
