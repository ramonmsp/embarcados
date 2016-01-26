# Embarcados
Projetos para a Disciplina Sistemas Embarcados.<br>
Alunos: Ramon Maciel  e Randler Ferraz <br>
----------------------------------------------

#I unidade

**SISTEMA DE VIGILÂNCIA →** O software deve monitorar o acelerômetro e o giroscópio. Ao perceber modificações<br>
nos dois sensores (deslocamentos e vibrações), o software deve emitir avisos sonoros e enviar um e-mail de alerta<br>
informando que o objeto vigiado foi movido do seu lugar. Deve ser utilizada a biblioteca JAVAMAIL.<br>

Os seguintes sensores serão utilizados para implementação desse sistema embarcado e alto nível: 
GY-80 → Responsavel por verificar o giroscopio e acelerometro;

#II unidade

**SISTEMA DE MONITORAMENTO DE VACINAS →**Monitorar o ambiente onde a vacina está armazenada, saber temperatura, umidade do ar e luminosidade.<br> 
Esse tipo de medicamento deve ficar exposto a temperatura, umidade do ar e nível de iluminação controlados. <br>
Esse controle é necessário, principalmente das vacinas fotossensíveis, por causa do custo de produção em massa e distribuição. <br> 

O sistema fará um alerta no software de alto nível, disponível ao usuário, em caso de alteração em qualquer um dos itens monitorados.<br>

O sistema embarcado trará a comodidade de eliminar verificação desses itens manualmente.<br> 
Evita que essa medicação, algumas de custo muito elevado, estrague por conta de condições ruins de armazenamento.<br> 

Os seguintes sensores serão utilizados para implementação desse sistema embarcado e alto nível: <br>
* DHT11 → Sensores de umidade do ar e temperatura; <br>
* LDR → Sensor de luminosidade; <br>
* RF → Sensor de receptor de rádio frequência.<br>

O emissor enviará os dados que os sensores capturarão:<br>
* Temperatura atual;<br>
* Umidade relativa do ar;<br>
* Indicativo de luminosidade.<br>

Previsto como as informações serão agrupadas em número(s) longo(s) para transmissão:<br>
* 4 bits para identificação, utilizado pelo RF; <br>
* 8 bits para a umidade (DHT 11);  <br>
* 8 bits para a Temperatura (DHT 11); <br> 
* 10 bits para a luminosidade (LDR).<br>

# III unidade

**SISTEMA DE MONITORAMENTO DE VACINAS →**consiste na adaptação da automação embarcada desenvolvida na UNIDADE II <br> 
de forma que ela adquira características de solução de software para a **WEB DAS COISAS**<br>

* Deverá ser desenvolvido um SERVIÇO WEB RESTful (utilizando a linguagem JAVA e a API Jersey) <br>
sobre uma instância de servidor TOMCAT. O Serviço Web deve estar integrado ao Driver de forma que<br>
consiga obter as últimas informações lidas a partir dos sensores;<br>

**O DRIVER deve conter as seguintes características:** <br>
* (i) ele deve ser capaz de ser iniciado e finalizado por um script de linha de comando (INIT.D);<br> 
* (ii) ele deve ser capaz de se comunicar com o Serviço Web através de um arquivo PIPE;<br>
* (iii)Deve ser possível testar todas as saídas de dados do Serviço Web através de um Browser;<br>

**O Serviço Web deve ser capaz de fornecer para aplicações-cliente:** 
* (i) os dados lidos dos sensores na forma como são repassados pelo driver;<br>
* (ii) diagnósticos sobre os dados lidos dos sensores <br>

**Criação de um Cliente de consumo das informações lidas a partir do Serviço Web**<br>
Este cliente deve utilizar o Serviço Web para exibir os valores (dos sensores) lidos e os diagnósticos realizados na forma<br>
de uma Aplicação Web gráfica. Idealmente, pode ser realizada a adaptação do Software Web desenvolvido na Unidade II<br>
para que ele se torne cliente do Serviço Web;<br>

--------------------------------------------------------

#Projeto 
**I unidade**<br>

**II unidade**<br>
![alt tag](https://github.com/ramonmsp/embarcados/blob/master/Vacina_image.jpg)


