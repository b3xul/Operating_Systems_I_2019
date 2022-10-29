#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

/*typedef enum sceltaMenu_e {
  uscita_c, stampa_video_c, stampa_file_c, ordina_data_c, ordina_cod_c,
  ordina_cogn_c, ordina_cat_c, aggiorna_ore_c, cerca_cod_c, cerca_cogn_c, numScelte_c
} sceltaMenu;

// si propone una tabella di conversione tra menu e stringhe, basata su
// vettore di struct, anziche' vettore con accesso diretto
struct {sceltaMenu codice; char *prompt; char *comando;} scelte[] = {
  {uscita_c, "Uscita", "Fine"},
  {stampa_video_c, "Stampa atleti a video", "Video"},
  {stampa_file_c, "Stampa atleti su file", "File"},
  {ordina_data_c, "Ordina per data di nascita", "Od"},
  {ordina_cod_c, "Ordina per codice atleta", "Ocod"},
  {ordina_cogn_c, "Ordina per cognome", "Ocogn"},
  {ordina_cat_c, "Ordina per categoria", "Ocat"},
  {aggiorna_ore_c, "Aggiorna monte ore", "Ore"},
  {cerca_cod_c, "Ricerca per codice", "Codice"},
  {cerca_cogn_c, "Ricerca per cognome", "Cognome"},
  {numScelte_c, NULL, NULL}
};*/

typedef enum sceltaMenu_enum{
    somma_c,differenza_c,fine_c,numScelte_c
} sceltaMenu;

struct{sceltaMenu codice; char* prompt; char* comando;} scelte[]={
    {somma_c,"Invia SIGUSR2 a PID","somma"},
    {differenza_c,"Invia SIGUSR1 a PID","differenza"},
    {fine_c,"Invia SIGINT a PID","fine"},
    {numScelte_c,NULL,NULL}
};

int main(int argc, char* argv[])
{
    if(argc!=3){
        fprintf(stderr,"Numero errato di argomenti (!=3)");
        exit(-1);
    }
    pid_t pid=atoi(argv[1]);
    int i;
    sceltaMenu selezione;

    for(i=0; i<numScelte_c; i++){
        printf("%s (%s)\n", scelte[i].prompt, scelte[i].comando);
        if (strcmp(argv[2],scelte[i].comando)==0) {
            selezione=scelte[i].codice;
        }
    }

    switch(selezione){
        case somma_c:
            kill(pid,SIGUSR2);
            break;
        case differenza_c:
            kill(pid,SIGUSR1);
            break;
        case fine_c:
            kill(pid,SIGINT);
            break;
        default:
            break;
    }
    return 0;
}
