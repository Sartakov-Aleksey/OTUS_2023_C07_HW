# 1) Нужно перейти в каталог/папку, в котором находится коревая папка вашего проекта на Си 
# Если проект только из одного файла = main.c, то нужно перейти в папку, где расположен этот файл
#  cd /home/postgres/Документы/_тесты_си/
# 2) и запустить исплняемую иснтрукцию (*sh. файл)
# ./запуск_сборки.sh 

# указываем директорию для хранения промежуточных смаке файлов и самой программы. В следующий раз компилирует только новые файлы
BIN_DIR=_bin_архив
# Указываем название каталога, в котором хранится ваш проект. (как подпапка относительно текущего каталога)
ISHODNIKI_DIR= "" # имя папки в которой лежит сам проект относительно предыдущей папки или глобальный адрес на ПК 








# ============================ ниже ничего не трогаем - все делается автоматически ==============
mkdir ${BIN_DIR}
cd ${BIN_DIR}

# список всех путей для поиска и работы
set PATH = /usr/bin/:%PATH%

# создаём инструкцию для последующей работы make файла 
cmake  ../${ISHODNIKI_DIR} -DCURL_DISABLE_*=1 -DCURL_DISABLE_DICT=1 -DCURL_DISABLE_FILE=1 -DCURL_DISABLE_FTP=1 -DCURL_DISABLE_FTPS=1 -DCURL_DISABLE_GOPHER=1 -DCURL_DISABLE_GOPHERS=1 -DCURL_DISABLE_IMAP=1 -DCURL_DISABLE_IMAPS=1 \
-DCURL_DISABLE_IPFS=1 -DCURL_DISABLE_IPNS=1  -DCURL_DISABLE_LDAP=1 -DCURL_DISABLE_LDAPS=1 \
-DCURL_DISABLE_MQTT=1 -DCURL_DISABLE_POP3=1 -DCURL_DISABLE_POP3S=1 -DCURL_DISABLE_RTSP=1 -DCURL_DISABLE_SMB=1 -DCURL_DISABLE_SMBS=1 -DCURL_DISABLE_SMTP=1 -DCURL_DISABLE_SMTPS=1 -DCURL_DISABLE_TFTP=1 


# Protocols: dict file ftp ftps gopher gophers http https imap imaps ipfs ipns 
# mqtt pop3 pop3s rtsp smb smbs smtp smtps telnet tftp

# запуск непосредственно самого make с подробным отчетом что делается. или же просто можно запустить  make
Verbose=1 make -j 8

