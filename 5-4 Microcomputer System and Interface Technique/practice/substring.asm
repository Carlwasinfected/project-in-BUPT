; ʹ��ѭ���ṹ�������ô�����

data segment
    s db 2000h dup(0)
    t db 200h dup(0)
    found db 0
    pos dw 0
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
    mov ax, data
    mov ds, ax
    mov es, ax 
    
    lea si ,s
    lea di ,t
    xor dx, dx
    
    mov byte ptr[si], 'h'
    mov byte ptr[si+1], 'e'
    mov byte ptr[si+2], 'l'
    mov byte ptr[si+3], 'l'
    mov byte ptr[si+4], 'o'
    mov byte ptr[si+5], '!'
    
    mov byte ptr[di], 'l'
    mov byte ptr[di+1], 'l'
    mov byte ptr[di+2], 'o'
    
main_loop:
    cmp [di], 00h  ; ����Ƚϵ����Ӵ���ĩβ����һ���ҵ���
    jz fd
    mov al, byte ptr[di]
    cmp al, byte ptr[si] ; �Ƚ�si��diָ��������ַ�
    jz same
    inc dx  ; ������� ��si������diλ�� ��di�������Ӵ���ʼλ��
    lea si, s
    add si, dx
    lea di, t
    cmp [si], 00h  ; ���Ƚϵ���Դ��ĩβ����һ��û���ҵ�
    jz not_fd
    jmp main_loop
    
fd:
    mov found, 0ffh
    mov pos, dx
    jmp fin 
    
not_fd:
    mov found, 00h
    jmp fin
 
same:
    inc si  ; ����ȣ��������ɨ��
    inc di
    jmp main_loop

fin:    
    mov ax, 4c00h
    int 21h    
ends

end start
