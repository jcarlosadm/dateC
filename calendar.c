/*
 * calendar.c
 *
 */

#include "calendar.h"

/*
 * Estrutura do objeto calendário
 *
 * Armazena data e hora
 */
struct calendar{
    // data em segundos desde 1900
    time_t date;
};

/* ******************************************
 * Funções do calendário
 ********************************************/

/*
 * Cria o calendário
 * Aloca memória para um objeto Calendar e
 * retorna um ponteiro para a memória alocada
 */
Calendar* createCalendar(){
    // aloca objeto Calendar
    Calendar* calendar = malloc(sizeof(Calendar));
    // configura data para hoje
    setDateToday(calendar);
    // retorna ponteiro para Calendar
    return calendar;
}

/*
 * Desaloca objeto Calendar, e retorna NULL
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ser desalocado
 */
Calendar* destroyCalendar(Calendar* calendar){
    // libera memória de calendar
    free(calendar);
    // retorna NULL
    return NULL;
}

/*
 * Configura a data do calendário para hoje
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ter a data configurada
 */
void setDateToday(Calendar* calendar){
    // configura data atual no objeto Calendar
    calendar->date = time(0);
}

/*
 * Define a data dos segundos a partir de 1900
 * Retorna true se conseguir, e false caso contrário
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ter a data configurada
 * time_t seconds : segundos desde 1900
 */
bool setDateOfSeconds(Calendar* calendar, time_t seconds){
    // se segundos menores que zero, retorna false
    if(seconds<0)
        return false;
    // caso contrário...
    else{
        // define nova data e retorna sucesso
        calendar->date = seconds;
        return true;
    }
}

/*
 * Retorna a data do calendário em segundos desde 1900
 *
 * Calendar* calendar : ponteiro para objeto Calendar
 */
time_t getDateInSeconds(Calendar* calendar){
    // retorna segundos totais desde 1900
    return calendar->date;
}

/*
 * Imprime no prompt a data em um formato pré-especificado
 *
 * Calendar* calendar : ponteiro para objeto Calendar
 * emun DateString dateString : enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * bool weekDayName : se o nome do dia da semana deve constar no final da string
 */
void printDate(Calendar* calendar, enum DateString dateString, bool weekDayName){
    // coloca data em uma estrutura struct tm (ver time.h)
    struct tm* tm = localtime(&(calendar->date));
    // imprime data em um formato específico
    printf("%d/%d/%d\n",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900);
}




/**
 * Lembrete para implementação
 * Para addCompontDate: se dia 29 do mês fevereiro, se add ano diferente de 4, -1 dia e +x ano
 *                      se dia 31 e add mes com menos dias, -1 (ou -2/-3 se fev) dia e +mes
 *                      se dia 30 e add mes fevereiro, -2 (ou -1) dia e +mes
 */
