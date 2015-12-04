# Embarcados
Projetos para a Disciplina Sistemas Embarcados.
Alunos: Ramon Maciel  e Randler Ferraz 

#I unidade

**SISTEMA DE VIGILÂNCIA →** O software deve monitorar o acelerômetro e o giroscópio. Ao perceber modificações
nos dois sensores (deslocamentos e vibrações), o software deve emitir avisos sonoros e enviar um e-mail de alerta
informando que o objeto vigiado foi movido do seu lugar. Deve ser utilizada a biblioteca JAVAMAIL.

Os seguintes sensores serão utilizados para implementação desse sistema embarcado e alto nível: 
GY-80 → Responsavel por verificar o giroscopio e acelerometro;

#II unidade

**SISTEMA DE MONITORAMENTO DE VACINAS →**Monitorar o ambiente onde a vacina está armazenada, saber temperatura, umidade do ar e luminosidade. 
Esse tipo de medicamento deve ficar exposto a temperatura, umidade do ar e nível de iluminação controlados. 
Esse controle é necessário, principalmente das vacinas fotossensíveis, por causa do custo de produção em massa e distribuição. 

O sistema fará um alerta no software de alto nível, disponível ao usuário, em caso de alteração em qualquer um dos itens monitorados.

O sistema embarcado trará a comodidade de eliminar verificação desses itens manualmente. 
Evita que essa medicação, algumas de custo muito elevado, estrague por conta de condições ruins de armazenamento. 

Os seguintes sensores serão utilizados para implementação desse sistema embarcado e alto nível: 
DHT11 → Sensores de umidade do ar e temperatura;
LDR → Sensor de luminosidade;
RF → Sensor de receptor de rádio frequência.

O emissor enviará os dados que os sensores capturarão:
Temperatura atual;
Umidade relativa do ar;
Indicativo de luminosidade.

Previsto como as informações serão agrupadas em número(s) longo(s) para transmissão:
4 bits para identificação, utilizado pelo RF;
8 bits para a umidade (DHT 11); 
8 para a Temperatura (DHT 11); 
10 para a luminosidade (LDR).

