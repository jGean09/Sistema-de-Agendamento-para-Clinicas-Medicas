struct medico{
    char CRM[13];
    char nome[51];
    char especializacao[31];
};


// MÉDICO
void tela_medico(void);
void tela_cadastrar_medico(void);
void tela_atualizar_medico(void);
void tela_deletar_medico(void);
void tela_ver_medico(void);
void solicitar_especializacao(char *especializacao);