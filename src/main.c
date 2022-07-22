#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void aggiungiGrafo(int*,int*,int,int);
int sommaCammini(int*,int);
void algDijkstra(int*,int*,int,int*);
void minHeap(int*,int*,int*,int);
int controllo(int*,int);
void swap_mH(int*,int*,int*,int,int);
void swap_MH(int*,int*,int,int);
void heapSortM(int*,int*,int);
void maxHeapify(int*,int*,int,int);

int main(){
    int d,k,indice=-1,i;
    char input[15];
    if(scanf("%d %d",&d,&k));
    int pesi[k+1],etichette[k+1];
    if(k==0){
    return 0;
    }
    while(getchar()!='\n');
    if(fgets(input,15,stdin));

    do{
        if(strcmp(input,"AggiungiGrafo\n")==0){
            indice++;
            if(indice<k)
                aggiungiGrafo(&pesi[indice+1],&etichette[indice+1],d,indice);
            else{
                if(indice==k)
                    heapSortM(&pesi[1],&etichette[1],k);
                aggiungiGrafo(&pesi[0],&etichette[0],d,indice);
                maxHeapify(&pesi[1],&etichette[1],k,0);
                if(pesi[0]<pesi[1]){
                    pesi[1]=pesi[0];
                    etichette[1]=etichette[0];
                }
            }
        }
        else{
            if(indice!=-1){
                if(indice<k){
                    for(i=1;i<indice+1;i++){
                        printf("%d ",etichette[i]);
                    }
                    printf("%d",etichette[i]);
                }
                else{
                    for(i=1;i<k;i++){
                        printf("%d ",etichette[i]);
                    }
                    printf("%d",etichette[i]);
                }
            }
            printf("\n");
        }
    }while(fgets(input,15,stdin)!=NULL);

    return 0;
}

void aggiungiGrafo(int* pesi,int* etichette,int d, int indice){
    int l=d*d,matrice[l],i,num=0;
    char c;
    for(i=0;i<l;i++){
        while((c=getchar())!='\n'){
            if(c!=','){
                num*=10;
                num+=c-'0';
            }
            else{
                matrice[i]=num;
                i++;
                num=0;
            }
        }
        matrice[i]=num;
        num=0;
    }
    *etichette=indice;
    *pesi=sommaCammini(matrice,d);
}

int sommaCammini(int* matrice,int d){
    int indici[d],pesi[d];
    int i,a=1,sum=0;
    indici[0]=0;
    pesi[0]=0;
    for(i=1;i<d;i++){
        indici[i]=i;
        pesi[i]=INT_MAX;
    }
    for(i=1;i<d;i++){
        if(matrice[i]!=0){
            a=0;
            i=d;
        }
    }
    if(a){
        return 0;
    }
    algDijkstra(pesi,indici,d,matrice);
    
    for(i=1;i<d;i++){
        if(pesi[i]!=INT_MAX)
            sum+=pesi[i];
    }
    return sum;
}

void algDijkstra(int* pesi,int* indici,int d,int* matrice){
    int i,j,a,b,c,current,dim=d,posizioni[d];
    for(i=0;i<d;i++)
        posizioni[i]=i;

    for(i=0;i<d;i++){
        a=indici[i]*d;
        for(j=1;j<d;j++){
            if(pesi[i]!=INT_MAX){
                b=a+j;
                c=matrice[b]+pesi[i];
                if(matrice[b]!=0 && j!=indici[i]){
                    current=posizioni[j];
                    if(c<pesi[current] || pesi[current]==INT_MAX){
                        pesi[current]=c;
                    }
                }
            }
        }
        dim--;
        if(dim>1)
            minHeap(&pesi[i+1],&indici[i+1],posizioni,dim);
    }
}

void minHeap(int* pesi,int* indici,int* posizioni,int d){
    int a,i,N=(d/2)+1,vec[N],parent,child,punt1,punt2;
    vec[0]=1;
    
    if(d==2){
        if(pesi[1]<pesi[0]){
            swap_mH(pesi,indici,posizioni,0,1);
        }
    }
    else{
        while(controllo(vec,N)){
            parent=N-1;
            for(i=0;i<N;i++){
                a=1;
                child=2*parent;
                if(parent-1>=0){
                    punt1=parent-1;
                    punt2=child-1;
                }
                else{
                    punt1=0;
                    punt2=0;
                }
                if(pesi[punt2]<pesi[punt1])
                    swap_mH(pesi,indici,posizioni,punt1,punt2);
                else{
                    if(punt2!=d-1){
                        punt2++;
                        if(pesi[punt2]<pesi[punt1])
                            swap_mH(pesi,indici,posizioni,punt1,punt2);
                        else
                            a=0;
                    }
                    else
                        a=0;
                    vec[i]=a;
                    parent--;
                }
            }
        }
    }
}

void heapSortM(int* pesi,int* indici,int d){
    int i;
    for (i=d/2-1;i>=0;i--)
        maxHeapify(pesi,indici,d,i);
}

void maxHeapify(int* pesi,int* indici,int d,int n){
    int l=2*n,r=2*n+1,posmax;
    if(l<=d && pesi[l]>pesi[n])
        posmax=l;
    else
        posmax=n;
    if(r<=d && pesi[r]>pesi[posmax])
        posmax=r;
    if(posmax!=n){
        swap_MH(pesi,indici,n,posmax);
        maxHeapify(pesi,indici,d,posmax);
    }
}

int controllo(int* vec,int d){
    int i;
    for(i=0;i<d;i++){
        if(vec[i]==1)
            return 1;
    }
    return 0;
}

void swap_mH(int* pesi,int* indici,int* posizioni,int a,int b){
    int x,alpha=indici[a],beta=indici[b];
    x=pesi[a];
    pesi[a]=pesi[b];
    pesi[b]=x;

    x=posizioni[alpha];
    posizioni[alpha]=posizioni[beta];
    posizioni[beta]=x;

    x=indici[a];
    indici[a]=indici[b];
    indici[b]=x;
}

void swap_MH(int* pesi,int* indici,int a,int b){
    int x;
    x=pesi[a];
    pesi[a]=pesi[b];
    pesi[b]=x;

    x=indici[a];
    indici[a]=indici[b];
    indici[b]=x;
}