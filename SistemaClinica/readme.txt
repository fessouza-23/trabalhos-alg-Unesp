COMO COMPILAR O PROGRAMA
1 - RODAR "MAKE" NA RAIZ DO DIRETORIO
3 - FIM

Trabalho de Algoritmos II - Gerenciamento de Clinica
a partir de manipulação de arquivos binarios
realizado por:
 - João Victor Fernandes Souza
 - Eduardo Rodrigues Teixeira
 - Gabriel Rasi
 - Guilherme Silva

--------------------------------------------------------------------------------------------------------------------------
INSTALANDO "MAKE" POR MEIO DO GERENCIADOR DE PACOTES "CHOCOLATEY" PARA WINDOWS

Se já possui make instalado na sua máquina, ignore este tutorial.

Obs: é necessário ter o gcc na sua máquina: Para isso, acesse: https://winlibs.com/#download-release > Baixar a versão adequada > Descompactar o arquivo no C:\ (não é necessário a instalação)

"WinLibs.com
Standalone MinGW-w64+GCC builds for Windows, built from scratch (including all dependencies) natively on Windows for Windows.

Downloads are archive files (.zip or .7z). No installation is required, just extract the archive and start using the programs in mingw32\bin or mingw64\bin. This allows for a relocatable compiler suite and allows having multiple versions on the same system."
Fonte: https://www.mingw-w64.org/downloads/

Link para o gerenciador de pacotes: https://chocolatey.org/install

1. Rodar cmd/Powershell como administrador (clique-direito > Executar como Administrador)

2. Executar comando "Get-ExecutionPolicy". Se retornar "Restricted", executar: "Set-ExecutionPolicy AllSigned" ou "Set-ExecutionPolicy Bypass -Scope Process" (SEM ASPAS)

3. Rodar o seguinte comando: 
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))

4. Rodar "choco" para verificar que a instalação obteve êxito (SEM ASPAS)

5. Rodar "choco install make". Atenção: para instalar pacotes, o cmd/Powershell deve estar rodando como admin (SEM ASPAS)

6. Após a instalação, basta executar o comando "make" no diretório do projeto (SEM ASPAS)
--------------------------------------------------------------------------------------------------------------------------
caso necessite:
executar na src para compilar informacoes e o icone do programa
windres my.rc -o coff -o my.res
