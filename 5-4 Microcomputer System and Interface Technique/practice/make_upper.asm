
data segment
    string db '***2016:i_love_wei_ji_jie_kou_!!!***do_you_believe_me!#hehe$'
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
    mov ax, data
    mov ds, ax
    mov es, ax
    lea si, string ; �õ�string�׵�ַ
    
comp:
    mov al, byte ptr [si]
    cmp al, '$' ; ������������������������ʾ���
    jz fin
    cmp al, 'a' ; ��������'a'С���ַ����򱻹�Ϊ����
    jb others
    cmp al, 'z' ; �ڴ˻�����������С�ڵ���'z'�ģ�����Сд��ĸ
    jbe islower
    jmp others  ; ��'z'��ı���Ϊ����
    
others:
    inc si      ; ����������ַ���������������
    jmp comp
    
islower:
    sub al, 32  ; ��ȥ32��Ϊ��д��ĸ
    mov [si], al
    inc si
    jmp comp
    
fin:
    mov dx, offset string  ; �����ʾ���ܣ��������ճ���...
    mov ax, 0900h
    int 21h
    mov ax, 4c00h  ; ���ز���ϵͳ
    int 21h    
ends

end start
