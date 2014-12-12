/*
 * date.c
 *
 */

#include "../h_files/date.h"

/*
 * Estrutura do objeto data
 *
 * Armazena data e hora
 */
struct date{
    // dados em segundos desde 1900
    time_t data;
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
        printf("Sunday ");
        break;

    case MONDAY:
        printf("Monday ");
        break;

    case TUESDAY:
        printf("Tuesday ");
        break;

    case WEDNESDAY:
        printf("Wednesday ");
        break;

    case THURSDAY:
        printf("Thursday ");
        break;

    case FRIDAY:
        printf("Friday ");
        break;

    case SATURDAY:
        printf("Saturday ");
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
    time_t data = mktime(&tm);

    return data;
}

/* ******************************************
 * Funções públicas da data
 ********************************************/

/*
 * Cria o data
 * Aloca memória para um objeto Date e
 * retorna um ponteiro para a memória alocada
 */
Date* createDate(){
    // aloca objeto Date
    Date* date = malloc(sizeof(Date));
    // configura data para hoje
    setDateToday(&date);
    // retorna ponteiro para Date
    return date;
}

/*
 * Desaloca objeto Date, e retorna NULL
 *
 * Date* date : ponteiro para objeto Date a ser desalocado
 */
Date* destroyDate(Date* date){
    // libera memória de date
    free(date);
    // retorna NULL
    return NULL;
}

/*
 * Configura a data para hoje
 *
 * Date* date : ponteiro para objeto Date a ter a data configurada
 */
void setDateToday(Date** date){
    // configura data atual no objeto Date
    (*date)->data = time(0);
}

/*
 * Configura uma data específica no data
 * Retorna true se conseguir, e false caso contrário
 *
 * Date* date : ponteiro para objeto Date a ter a data configurada
 * int day : dia do mês
 * int month : mês
 * int year : ano
 */
bool setDatePartial(Date** date, int day, int month, int year){

    if(!validateDate(day,month,year,0,0,0)) return false;

    // constrói uma data com os valores passados
    time_t data = makeDate(day,month,year,0,0,0);

    // se conseguiu passar para segundos ...
    if(data != -1){
        // sucesso
        (*date)->data = data;
        return true;
    }
    // caso contrário retorna false
    else
        return false;

}

/*
 * Configura a data completa
 * Retorna true se conseguir, e false caso contrário
 *
 * Date* date : ponteiro para objeto Date a ter a data configurada
 * int day : dia do mês
 * int month : mês
 * int year: ano
 * int hour : hora
 * int minute : minuto
 * int second : segundo
 */
bool setDateComplete(Date** date, int day, int month, int year,
        int hour, int minute, int second){

    if(!validateDate(day,month,year,hour,minute,second))return false;

    // constrói uma data com os valores passados
    time_t data = makeDate(day,month,year,hour,minute,second);

    // se conseguiu passar para segundos ...
    if(data != -1){
        // sucesso
        (*date)->data = data;
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
 * Date* date : ponteiro para objeto Date a ter a data configurada
 * time_t seconds : segundos desde 1900
 */
bool setDateOfSeconds(Date** date, time_t seconds){
    // se segundos menores que zero, retorna false
    if(seconds<0)
        return false;
    // caso contrário...
    else{
        // define nova data e retorna sucesso
        (*date)->data = seconds;
        return true;
    }
}

/*
 * Retorna a data em segundos desde 1900
 *
 * Date* date : ponteiro para objeto Date
 */
time_t getDateInSeconds(Date** date){
    // retorna segundos totais desde 1900
    return (*date)->data;
}

/*
 * Retorna um componente da data (dia, mês, ano, hora ...)
 * Retorna -1 se, por algum motivo, não conseguir retorna o solicitado
 *
 * Date* date : ponteiro para objeto Date
 * enum DateComponent dateComponent : enumerador que indica a parte da data
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
int getDateComponent(Date** date, enum DateComponent dateComponent){
    
    struct tm* tm = localtime(&((*date)->data));
    
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
 * Date* date : ponteiro para objeto Date
 * emun DateString dateString : enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * bool weekDayName : se o nome do dia da semana deve constar no final da string
 * char* dateStringComp : ponteiro para string literal
 *
 * Obs: para char = 1byte, considere que a área de memória para onde o ponteiro
 * da string literal aponta tenha pelo menos 10 bytes.
 */
bool getStringDate(Date** date, enum DateString dateString,
        bool weekDayName, char* dateStringComp){
    
    struct tm* tm = localtime(&((*date)->data));
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
        if(sprintf(dateStringComp,"%d/%d/%d%c",day,month,year,0) < 0)return false;
        break;
    case DATE_YMD:
        if(sprintf(dateStringComp,"%d/%d/%d%c",year,month,day,0) < 0)return false;
        break;
    case DATE_HMS:
        if(sprintf(dateStringComp,"%d:%d:%d%c",hour,min,sec,0) < 0)return false;
        break;
    case DATE_HMS_AMPM:
        if(sprintf(dateStringComp,"%d:%d:%d %s%c",hour,min,sec,ampm,0) < 0)return false;
        break;
    case DATE_DMY_HMS:
        if(sprintf(dateStringComp,"%d/%d/%d %d:%d:%d%c",day,month,year,hour,min,sec,0) < 0)return false;
        break;
    case DATE_YMD_HMS:
        if(sprintf(dateStringComp,"%d/%d/%d %d:%d:%d%c",year,month,day,hour,min,sec,0) < 0)return false;
        break;
    case DATE_DMY_HMS_AMPM:
        if(sprintf(dateStringComp,"%d/%d/%d %d:%d:%d %s%c",day,month,year,hour,min,sec,ampm,0) < 0)
            return false;
        break;
    case DATE_YMD_HMS_AMPM:
        if(sprintf(dateStringComp,"%d/%d/%d %d:%d:%d %s%c",year,month,day,hour,min,sec,ampm,0) < 0)
            return false;
    }
    
    if(weekDayName){
        
        switch(tm->tm_wday){
        case SUNDAY:
            if(sprintf(dateStringComp,"%s Sunday%c",dateStringComp,0) < 0)return false;
            break;
        case MONDAY:
            if(sprintf(dateStringComp,"%s Monday%c",dateStringComp,0) < 0)return false;
            break;
        case TUESDAY:
            if(sprintf(dateStringComp,"%s Tuesday%c",dateStringComp,0) < 0)return false;
            break;
        case WEDNESDAY:
            if(sprintf(dateStringComp,"%s Wednesday%c",dateStringComp,0) < 0)return false;
            break;
        case THURSDAY:
            if(sprintf(dateStringComp,"%s Thursday%c",dateStringComp,0) < 0)return false;
            break;
        case FRIDAY:
            if(sprintf(dateStringComp,"%s Friday%c",dateStringComp,0) < 0)return false;
            break;
        case SATURDAY:
            if(sprintf(dateStringComp,"%s Saturday%c",dateStringComp,0) < 0)return false;
        }
    }
    
    return true;

}

/*
 * Gera uma string do dia da semana e o retorna
 *
 * Date* date : ponteiro para o objeto Date
 * char* dateStringComp : ponteiro para string literal
 *
 * Obs: para char = 1byte, considere que a área de memória para onde o ponteiro
 * da string literal aponta tenha pelo menos 10 bytes.
 */
bool getStringWeekDay(Date** date, char* stringComp){

    struct tm* tm = localtime(&((*date)->data));

    switch(tm->tm_wday){
    case SUNDAY:
        if(sprintf(stringComp,"Sunday%c",0) < 0)return false;
        break;
    case MONDAY:
        if(sprintf(stringComp,"Monday%c",0) < 0)return false;
        break;
    case TUESDAY:
        if(sprintf(stringComp,"Tuesday%c",0) < 0)return false;
        break;
    case WEDNESDAY:
        if(sprintf(stringComp,"Wednesday%c",0) < 0)return false;
        break;
    case THURSDAY:
        if(sprintf(stringComp,"Thursday%c",0) < 0)return false;
        break;
    case FRIDAY:
        if(sprintf(stringComp,"Friday%c",0) < 0)return false;
        break;
    case SATURDAY:
        if(sprintf(stringComp,"Saturday%c",0) < 0)return false;
    }

    return true;
}

/*
 * Adiciona (ou subtrai) uma quantidade em uma componente específica da data
 * Retorna false se não conseguir, e true em caso contrário
 *
 * Date* date : ponteiro para o objeto Date
 * enum DateComponent dateComponent : enumerador que indica a parte da data
 *      a ser operado (veja o enumerador neste header file)
 * int value : valor a ser adicionado (ou subtraído) na componente de data
 * bool add : se true, adiciona. se false, subtrai
 */
bool addComponentDate(Date** date, enum DateComponent dateComponent, int value, bool add){
    struct tm* tm = localtime(&((*date)->data));

    switch(dateComponent){
    case MDAY:
        if(add) tm->tm_mday += value;
        else tm->tm_mday -= value;
        break;
    case YDAY:
        if(add) tm->tm_yday += value;
        else tm->tm_yday -= value;
        break;
    case WDAY:
        if(add) tm->tm_wday += value;
        else tm->tm_wday -= value;
        break;
    case MONTH:
        if(add) tm->tm_mon += value;
        else tm->tm_mon -= value;
        break;
    case YEAR:
        if(add) tm->tm_year += value;
        else tm->tm_year -= value;
        break;
    case HOUR:
        if(add) tm->tm_hour += value;
        else tm->tm_hour -= value;
        break;
    case HOUR_AMPM:
        if(add) tm->tm_hour += value;
        else tm->tm_hour -= value;
        break;
    case MINUTE:
        if(add) tm->tm_min += value;
        else tm->tm_min -= value;
        break;
    case SECOND:
        if(add) tm->tm_sec += value;
        else tm->tm_sec -= value;
    }

    time_t date2 = mktime(tm);

    if(date2 != -1){
        (*date)->data = date2;
        return true;
    }
    else
        return false;
}

/*
 * Imprime no prompt a data em um formato pré-especificado
 *
 * Date* date : ponteiro para objeto Date
 * emun DateString dateString : enumerador que indica qual o formato da string
 *      a ser utilizado (veja o enumerador neste header file)
 * bool weekDayName : se o nome do dia da semana deve constar no final da string
 */
void printDate(Date** date, enum DateString dateString, bool weekDayName){
    // coloca data em uma estrutura struct tm (ver time.h)
    struct tm* tm = localtime(&((*date)->data));

    // imprime de acordo com o formato determinado em dateString
    switch(dateString){

    case DATE_DMY:
        printf("%d/%d/%d ",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900);
        break;

    case DATE_YMD:
        printf("%d/%d/%d ",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
        break;

    case DATE_HMS:
        printf("%d:%d:%d ",tm->tm_hour,tm->tm_min,tm->tm_sec);
        break;

    case DATE_HMS_AMPM:
        printf("%d:%d:%d ",getHourInAmPm(tm->tm_hour),tm->tm_min,tm->tm_sec);
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            printf("AM ");
        else
            printf("PM ");
        break;

    case DATE_DMY_HMS:
        printf("%d/%d/%d %d:%d:%d ",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900,
                tm->tm_hour,tm->tm_min,tm->tm_sec);
        break;

    case DATE_YMD_HMS:
        printf("%d/%d/%d %d:%d:%d ",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,
                tm->tm_hour,tm->tm_min,tm->tm_sec);
        break;

    case DATE_DMY_HMS_AMPM:
        printf("%d/%d/%d %d:%d:%d ",tm->tm_mday,tm->tm_mon+1,tm->tm_year+1900,
                getHourInAmPm(tm->tm_hour),tm->tm_min,tm->tm_sec);
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            printf("AM ");
        else
            printf("PM");
        break;

    case DATE_YMD_HMS_AMPM:
        printf("%d/%d/%d %d:%d:%d ",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,
                getHourInAmPm(tm->tm_hour),tm->tm_min,tm->tm_sec);
        if(getAmPmSystem(tm->tm_hour) == AM_SYSTEM)
            printf("AM ");
        else
            printf("PM ");
    }

    // imprime o nome do dia da semana, se foi solicitado
    if(weekDayName){
        printWeek(tm->tm_wday);
    }

    // dá quebra de linha
    printf("\n");

}

/*
 * Imprime o nome do dia da semana no prompt
 *
 * Date* date : ponteiro para o objeto Date
 */
void printWeekDate(Date** date){
    struct tm* tm = localtime(&((*date)->data));

    printWeek(tm->tm_wday);
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
