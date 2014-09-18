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

/*
 * enumerador que indica AM ou PM
 */
enum AMPMSystem {
    AM_SYSTEM,
    PM_SYSTEM
};

/* *****************************************
 * Funções privadas
 *******************************************/

/*
 * Pega hora em formato 24 horas e devolve em formato AM PM
 */
int getHourInAmPm(int hour){
    int returning;

    if(hour == 0)
        returning = 12;
    else if(hour > 12 && hour < 24)
        returning = (hour - 12);

    return returning;
}

/*
 * Pega hora em formato 24 horas e devolve se corresponde a
 * AM ou PM
 */
int getAmPmSystem(int hour){
    if(hour >= 0 && hour < 12)
        return AM_SYSTEM;
    else
        return PM_SYSTEM;
}

/* ******************************************
 * Funções públicas do calendário
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

    // imprime de acordo com o formato determinado em dateString
    switch(dateString){

    case DATE_DMY:
        printf("%d/%d/%d",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900);
        break;

    case DATE_YMD:
        printf("%d/%d/%d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
        break;

    case DATE_HMS:
        printf("%d:%d:%d",tm->tm_hour,tm->tm_min,tm->tm_sec);
        break;

    case DATE_HMS_AMPM:
        printf("%d:%d:%d",getHourInAmPm(tm->tm_hour),tm->tm_min,tm->tm_sec);
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            printf(" AM");
        else
            printf(" PM");
        break;

    case DATE_DMY_HMS:
        printf("%d/%d/%d %d:%d:%d",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900,
                tm->tm_hour,tm->tm_min,tm->tm_sec);
        break;

    case DATE_YMD_HMS:
        printf("%d/%d/%d %d:%d:%d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,
                tm->tm_hour,tm->tm_min,tm->tm_sec);
        break;

    case DATE_DMY_HMS_AMPM:
        printf("%d/%d/%d %d:%d:%d",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900,
                getHourInAmPm(tm->tm_hour),tm->tm_min,tm->tm_sec);
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            printf(" AM");
        else
            printf(" PM");
        break;

    case DATE_YMD_HMS_AMPM:
        printf("%d/%d/%d %d:%d:%d",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,
                getHourInAmPm(tm->tm_hour),tm->tm_min,tm->tm_sec);
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            printf(" AM");
        else
            printf(" PM");
    }

    // imprime o nome do dia da semana, se foi solicitado
    if(weekDayName){
        switch(tm->tm_wday){
        case SUNDAY:
            printf(" Sunday");
            break;

        case MONDAY:
            printf(" Monday");
            break;

        case TUESDAY:
            printf(" Tuesday");
            break;

        case WEDNESDAY:
            printf(" Wednesday");
            break;

        case THURSDAY:
            printf(" Thursday");
            break;

        case FRIDAY:
            printf(" Friday");
            break;

        case SATURDAY:
            printf(" Saturday");
        }
    }

    // dá quebra de linha
    printf("\n");

}




/**
 * Lembrete para implementação
 * Para addCompontDate: se dia 29 do mês fevereiro, se add ano diferente de 4, -1 dia e +x ano
 *                      se dia 31 e add mes com menos dias, -1 (ou -2/-3 se fev) dia e +mes
 *                      se dia 30 e add mes fevereiro, -2 (ou -1) dia e +mes
 */
