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
    // string que guarda uma composição de data quando solicitado
    char* dateStringComp;
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
 *
 * int hour : hora em formato 24 horas
 */
int getHourInAmPm(int hour){
    int returning;

    if(hour == 0)
        returning = 12;
    else if(hour > 12 && hour < 24)
        returning = (hour - 12);
    else
        returning = hour;

    return returning;
}

/*
 * Pega hora em formato 24 horas e devolve valor de AM_SYSTEM ou
 * PM_SYSTEM
 *
 * int hour : hora em formato de 24 horas
 */
int getAmPmSystem(int hour){
    if(hour >= 0 && hour < 12)
        return AM_SYSTEM;
    else
        return PM_SYSTEM;
}

/*
 * Imprime o dia da semana de acordo com o valor fornecido
 *
 * int weekDay : dia da semana (0 - 6, começando pelo Domingo)
 */
void printWeek(int weekDay){

    // imprime uma string de acordo com o dia da semana
    switch(weekDay){
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

/*
 * Cria data em segundos desde 1900
 */
time_t makeDate(int day,int month,int year,int hour,int minute,int second){

    // constrói uma data com os valores passados
    struct tm tm;
    tm.tm_mday = day;
    tm.tm_mon = month - 1;
    tm.tm_year = year - 1900;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = second;

    // passa para o formato em segundos desde 1900
    time_t date = mktime(&tm);

    return date;
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
    // aloca string de composição de data
    calendar->dateStringComp = malloc(sizeof(char)*40);
    // retorna ponteiro para Calendar
    return calendar;
}

/*
 * Desaloca objeto Calendar, e retorna NULL
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ser desalocado
 */
Calendar* destroyCalendar(Calendar* calendar){
    // desaloca string de composição de data
    free(calendar->dateStringComp);
    // atrinbui ponteiro de composição de data para NULL
    calendar->dateStringComp = NULL;
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
 * Configura uma data específica no calendário
 * Retorna true se conseguir, e false caso contrário
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ter a data configurada
 * int day : dia do mês
 * int month : mês
 * int year : ano
 */
bool setDatePartial(Calendar* calendar, int day, int month, int year){

    if(!validateDate(day,month,year,0,0,0)) return false;

    // constrói uma data com os valores passados
    time_t date = makeDate(day,month,year,0,0,0);

    // se conseguiu passar para segundos ...
    if(date != -1){
        // sucesso
        calendar->date = date;
        return true;
    }
    // caso contrário retorna false
    else
        return false;

}

/*
 * Configura a data completa do calendário
 * Retorna true se conseguir, e false caso contrário
 *
 * Calendar* calendar : ponteiro para objeto Calendar a ter a data configurada
 * int day : dia do mês
 * int month : mês
 * int year: ano
 * int hour : hora
 * int minute : minuto
 * int second : segundo
 */
bool setDateComplete(Calendar* calendar, int day, int month, int year,
        int hour, int minute, int second){

    if(!validateDate(day,month,year,hour,minute,second))return false;

    // constrói uma data com os valores passados
    time_t date = makeDate(day,month,year,hour,minute,second);

    // se conseguiu passar para segundos ...
    if(date != -1){
        // sucesso
        calendar->date = date;
        return true;
    }
    // caso contrário retorna false
    else
        return false;

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
 * Retorna um componente do calendário (dia, mês, ano, hora ...)
 * Retorna -1 se, por algum motivo, não conseguir retorna o solicitado
 *
 * Calendar* calendar : ponteiro para objeto Calendar
 * enum DateComponent dateComponent : enumerador que indica a parte do calendário
 *      a ser retornado (veja o enumerador neste header file)
 *
 * Obs: alguns retornos específicos:
 * dia do mês: 1 - 31
 * dia do ano: 1 - 365
 * dia da semana: 0(para domingo) - 6(para sábado)
 * mês: 1-12
 * hora: 0-23
 * hora_ampm: 1-12
 * outros: formatos esperados
 */
int getDateComponent(Calendar* calendar, enum DateComponent dateComponent){
    
    struct tm* tm = localtime(&(calendar->date));
    
    switch(dateComponent){
    case MDAY:
        return tm->tm_mday;
    case YDAY:
        return tm->tm_yday;
    case WDAY:
        return tm->tm_wday;
    case MONTH:
        return (tm->tm_mon + 1);
    case YEAR:
        return (tm->tm_year + 1900);
    case HOUR:
        return tm->tm_hour;
    case HOUR_AMPM:
        return getHourInAmPm(tm->tm_hour);
    case MINUTE:
        return tm->tm_min;
    case SECOND:
        return tm->tm_sec;
    default:
        return -1;
    }
    
}

/*
 * Gera uma string e retorna um ponteiro para essa string
 *
 * Calendar* calendar : ponteiro para objeto Calendar
 * emun DateString dateString : enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * bool weekDayName : se o nome do dia da semana deve constar no final da string
 */
char* getStringDate(Calendar* calendar, enum DateString dateString,
        bool weekDayName){
    
    struct tm* tm = localtime(&(calendar->date));
    int day,month,year,hour,min,sec;
    char ampm[3];
    
    if(dateString==DATE_DMY || dateString==DATE_YMD || dateString==DATE_DMY_HMS
        || dateString==DATE_YMD_HMS || dateString==DATE_DMY_HMS_AMPM
        || dateString==DATE_YMD_HMS_AMPM){
        day = tm->tm_mday;
        month = tm->tm_mon+1;
        year = tm->tm_year+1900;
    }
    
    if(dateString==DATE_HMS || dateString==DATE_DMY_HMS || dateString==DATE_YMD_HMS){
        hour = tm->tm_hour;
        min = tm->tm_min;
        sec = tm->tm_sec;
    }
    
    if(dateString==DATE_HMS_AMPM || dateString==DATE_DMY_HMS_AMPM
        || dateString==DATE_YMD_HMS_AMPM){
        hour = getHourInAmPm(tm->tm_hour);
        min = tm->tm_min;
        sec = tm->tm_sec;
        strcpy(ampm,(getAmPmSystem(tm->tm_hour)==AM_SYSTEM ? "AM\0":"PM\0"));
    }
    
    switch(dateString){
    
    case DATE_DMY:
        sprintf(calendar->dateStringComp,"%d/%d/%d%c",day,month,year,0);
        break;
    case DATE_YMD:
        sprintf(calendar->dateStringComp,"%d/%d/%d%c",year,month,day,0);
        break;
    case DATE_HMS:
        sprintf(calendar->dateStringComp,"%d:%d:%d%c",hour,min,sec,0);
        break;
    case DATE_HMS_AMPM:
        sprintf(calendar->dateStringComp,"%d:%d:%d %s%c",hour,min,sec,ampm,0);
        break;
    case DATE_DMY_HMS:
        sprintf(calendar->dateStringComp,"%d/%d/%d %d:%d:%d%c",day,month,year,hour,min,sec,0);
        break;
    case DATE_YMD_HMS:
        sprintf(calendar->dateStringComp,"%d/%d/%d %d:%d:%d%c",year,month,day,hour,min,sec,0);
        break;
    case DATE_DMY_HMS_AMPM:
        sprintf(calendar->dateStringComp,"%d/%d/%d %d:%d:%d %s%c",day,month,year,hour,min,sec,ampm,0);
        break;
    case DATE_YMD_HMS_AMPM:
        sprintf(calendar->dateStringComp,"%d/%d/%d %d:%d:%d %s%c",year,month,day,hour,min,sec,ampm,0);
    }
    
    if(weekDayName){
        
        switch(tm->tm_wday){
        case SUNDAY:
            sprintf(calendar->dateStringComp,"%s Sunday%c",calendar->dateStringComp,0);
            break;
        case MONDAY:
            sprintf(calendar->dateStringComp,"%s Monday%c",calendar->dateStringComp,0);
            break;
        case TUESDAY:
            sprintf(calendar->dateStringComp,"%s Tuesday%c",calendar->dateStringComp,0);
            break;
        case WEDNESDAY:
            sprintf(calendar->dateStringComp,"%s Wednesday%c",calendar->dateStringComp,0);
            break;
        case THURSDAY:
            sprintf(calendar->dateStringComp,"%s Thursday%c",calendar->dateStringComp,0);
            break;
        case FRIDAY:
            sprintf(calendar->dateStringComp,"%s Friday%c",calendar->dateStringComp,0);
            break;
        case SATURDAY:
            sprintf(calendar->dateStringComp,"%s Saturday%c",calendar->dateStringComp,0);
        }
    }
    
    return (calendar->dateStringComp);
    
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
        printWeek(tm->tm_wday);
    }

    // dá quebra de linha
    printf("\n");

}

/*
 * Verifica se uma data é válida
 * Retorna false em caso negativo
 *
 * int day : dia
 * int month : mês
 * int year : ano
 * int hour : hora
 * int minute : minuto
 * int second : segundo
 */
bool validateDate(int day,int month,int year,int hour,int minute,int second){

    // primeira checagem
    if(second<0 || second>59)
        return false;
    else if(minute<0 || minute>59)
        return false;
    else if(hour<0 || hour>23)
        return false;
    else if(month<1 || month>12)
        return false;
    else if(day<1 || day>31)
        return false;

    // agora vamos validar o dia
    switch(month){
    case 2:
        if(year%4==0){
            if(day>29) return false;
        }
        else if(day>28)return false;
        break;
    case 4:
        if(day>30)return false;
        break;
    case 6:
        if(day>30)return false;
        break;
    case 9:
        if(day>30)return false;
        break;
    case 11:
        if(day>30)return false;
    }

    return true;

}


/**
 * Lembrete para implementação
 * Para addCompontDate: se dia 29 do mês fevereiro, se add ano diferente de 4, -1 dia e +x ano
 *                      se dia 31 e add mes com menos dias, -1 (ou -2/-3 se fev) dia e +mes
 *                      se dia 30 e add mes fevereiro, -2 (ou -1) dia e +mes
 */
