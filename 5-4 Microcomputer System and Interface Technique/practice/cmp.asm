; multi-segment executable file template.

data segment
    buff dw 200h
    n1 dw 0
    n2 dw 0
    n3 dw 0
ends

stack segment
    dw   128  dup(0)
ends

code segment
start:
; set segment registers:
        mov ax, data
        mov ds, ax
        mov es, ax

        mov cx  ,400          ;ѭ��������ÿ��ѭ��cx-2��ʵ��ѭ��200��
        mov [0211h] , 0ffffh  ;����һ����������������
        mov [0212h] , 01fffh  ;����һ����������������
        
rotate: mov ax ,buff          ;��ѭ�����Ӻ���ǰ����ɨ��
        mov bx ,cx
        add bx , ax
        mov ax , word ptr [bx] 
        cmp ax ,0     
        jz zero
        shl ax  ,1            ;ͨ�����Ʋ������õ�����λ
        jc plus
        jmp minus

zero:   inc n2
        dec cx
        loop rotate
        jmp fin

plus:   inc n1
        dec cx
        loop rotate
        jmp fin
        
minus:  inc n3
        dec cx
        loop rotate
        jmp fin

fin:
    mov ax, 4c00h 
    int 21h    
ends

end start
