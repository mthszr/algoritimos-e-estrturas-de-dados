// https://iudex.io/problem/5bcc95305cd44b0001fdbf74

#include<stdio.h>
#include<algorithm> // swap

int t,n,m,w,q,x,y,linha,num,par[10005],sz[10005];

int find(int a) {
    if (par[a] == a) return a;
    return par[a] = find(par[a]);
}

void join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) std::swap(a,b);
    sz[a] += sz[b];
    par[b] = a;
}

int main()
{
    scanf("%d",&t);

    for (int caso = 0; caso < t; caso++) {
        
        scanf("%d %d %d", &n,&m,&q);

        for (int i = 0; i < n*n; i++) par[i] = i, sz[i] = 1;
        
        for (int i = 0; i < m; i++) {
            scanf("%d",&w);
            linha = w / (2*n - 1); // 2n-1 paredes por linha
            num = w % (2*n - 1); // para uma dada linha, numerando colunas de 0 a 2n-2. as primeiras n-1 sÃ£o verticais.
            if (num < n-1) join(linha*n + num, linha*n + num + 1); // parede vertical: junta a com a+1
            else join(linha*n + num-(n-1), linha*n + n + num-(n-1)); // parede horizontal: junta a com a+n
        }
        
        for (int i = 0; i < q; i++){
            scanf("%d %d", &x, &y);
            printf("%d.%d %d\n",caso,i,find(x) == find(y));
        }        
        printf("\n");
    } 
}