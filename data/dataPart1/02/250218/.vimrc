set guifont=Courier_New:h10:cANSI   " 设置字体  
set ruler           " 显示标尺  
set foldenable      " 允许折叠  
set helplang=cn 
set termencoding=utf-8
set encoding=utf-8

""实用设置

" 设置当文件被改动时自动载入
set autoread
"代码补全 
" 启用插入模式下的关键词补全
set completeopt+=longest,menuone             " 提供更友好的补全菜单样式
set wildmenu                                 " 在命令行中启用菜单式补全
set wildmode=list:longest                    " 补全模式改为列出最长匹配项
"允许插件  
"打开文件类型检测, 加了这句才可以用智能补全
set nocompatible
filetype off

" Vundle settings
"set rtp+=~/.vim/bundle/Vundle.vim
"call vundle#begin()

"共享剪贴板  
set clipboard+=unnamed 
"从不备份  
set nobackup
"make 运行
:set makeprg=g++\ -Wall\ \ %
"自动保存
set autowrite
set cursorline              " 突出显示当前行
set guioptions-=T           " 隐藏工具栏
set guioptions-=m           " 隐藏菜单栏
set foldcolumn=0
set foldmethod=indent 
set foldlevel=3 
set foldenable              " 开始折叠
" 不要使用vi的键盘模式，而是vim自己的
set nocompatible
" 语法高亮
set syntax=on
" 去掉输入错误的提示声音
set noeb
" 在处理未保存或只读文件的时候，弹出确认
set confirm
" 自动缩进
set autoindent
set cindent
set cinoptions=cindent:res:12:4:5:6:7:12:16
" Tab键的宽度
set tabstop=4
" 统一缩进为4
set softtabstop=4
set shiftwidth=4
" 不要用空格代替制表符
set noexpandtab
" 在行和段开始处使用制表符
set smarttab
" 显示行号
set number
" 历史记录数
set history=1000
"禁止生成临时文件
set nobackup
set noswapfile
"搜索忽略大小写
set ignorecase
"编码设置
set enc=utf-8
set fencs=utf-8,ucs-bom,shift-jis,gb18030,gbk,gb2312,cp936
" 侦测文件类型
filetype on
" 载入文件类型插件
filetype plugin on
" 为特定文件类型载入相关缩进文件
filetype indent on
" 保存全局变量
set viminfo+=!
" 带有如下符号的单词不要被换行分割
set iskeyword+=_,$,@,%,#,-
" 字符间插入的像素行数目
set linespace=0
" 增强模式中的命令行自动完成操作
set wildmenu
" 使回格键（backspace）正常处理indent, eol, start等
set backspace=2
" 允许backspace和光标键跨越行边界
set whichwrap+=<,>,h,l
" 可以在buffer的任何地方使用鼠标（类似office中在工作区双击鼠标定位）
set mouse-=a
set selection=exclusive
set selectmode=mouse,key
" 在被分割的窗口间显示空白，便于阅读
set fillchars=vert:\ ,stl:\ ,stlnc:\
" 为C程序提供自动缩进
set smartindent
" 高亮显示普通txt文件（需要txt.vim脚本）
au BufRead,BufNewFile *  setfiletype txt
"自动补全
:inoremap ( ()<ESC>i
:inoremap ) <c-r>=ClosePair(')')<CR>
:inoremap { {}<ESC>i
:inoremap } <c-r>=ClosePair('}')<CR>
:inoremap [ []<ESC>i
:inoremap ] <c-r>=ClosePair(']')<CR>
:inoremap " ""<ESC>i
function! ClosePair(char)
    if getline('.')[col('.') - 1] == a:char
        return "\<Right>"
    else
        return a:char
    endif
endfunction


"""""""""""""""""""""""""""""新文件标题"""""""""""""""""""""""""""""""""""""

"新建.c,.h,.sh,.java文件，自动插入文件头 
autocmd BufNewFile *.cc,*.cpp,*.[ch],*.sh,*.java exec ":call SetTitle()" 
""定义函数SetTitle，自动插入文件头 
func SetTitle() 
    "如果文件类型为.sh文件 
    if &filetype == 'sh' 
        call setline(1,"\###################################################################################") 
        call append(line("."),   "\# File Name:    ".expand("%")) 
        call append(line(".")+1, "\# Author:		SuperYu") 
        call append(line(".")+2, "\# Mail:          yujian001002@163.com") 
        call append(line(".")+3, "\# Created Time: ".strftime("%c")) 
        call append(line(".")+4, "\###################################################################################") 
        call append(line(".")+5, "\#!/bin/bash") 
        call append(line(".")+6, "") 
    else 
        call setline(1, "/***************************************************") 
        call append(line("."),   "# File Name:    ".expand("%")) 
        call append(line(".")+1, "# Author:       SuperYu") 
        call append(line(".")+2, "# Mail:         yujian001002@163.com.com") 
        call append(line(".")+3, "# Created Time: ".strftime("%c")) 
        call append(line(".")+4, "****************************************************/") 
        call append(line(".")+5, "")
    endif
	if &filetype == 'cc'
        call append(line(".")+6, "#include <iostream>")
        call append(line(".")+7, "using namespace std;")
        call append(line(".")+8, "")
		call append(line(".")+9, "int main(int argc, char *argv[]) {")
		call append(line(".")+10, "")
		call append(line(".")+11, "    return 0;")
		call append(line(".")+12, "}")
	endif
    if &filetype == 'cpp'
        call append(line(".")+6, "#include <iostream>")
        call append(line(".")+7, "using namespace std;")
        call append(line(".")+8, "")
		call append(line(".")+9, "int main(int argc, char *argv[]) {")
		call append(line(".")+10, "")
		call append(line(".")+11, "    return 0;")
		call append(line(".")+12, "}")
	endif
    if &filetype == 'c'
		call append(line(".")+6, "#include <stdio.h>")
        call append(line(".")+7, " ")
		call append(line(".")+8, "int main(int argc, char *argv[]) {")
		call append(line(".")+9, "")
		call append(line(".")+10, "    return 0;")
		call append(line(".")+11, "}")
	endif
    autocmd BufNewFile * normal G
endfunc 


"键盘命令

nmap <leader>w :w!<cr>
nmap <leader>f :find<cr>

nmap <C-S> :w<CR>				" 在普通模式下映射Ctrl+S为保存命令 
" imap <C-S> <Esc>:w<CR>i		" 退出模式再保存 
inoremap <C-S> <Esc>:w<CR>a	
vmap <C-S> <C-C>:w<CR>gv		" 在可视模式下映射Ctrl+S（注意这里可因为 C-C 通常用于取消当前命令）


" 映射全选+复制 ctrl+a
map <C-A> ggVGY
map! <C-A> <Esc>ggVGY
map <F12> gg=G
" 选中状态下 Ctrl+c 复制
vmap <C-c> "+y
"去空行  
nnoremap <F2> :g/^\s*$/d<CR> 
"比较文件  
nnoremap <C-F2> :vert diffsplit 
"新建标签  
map <M-F2> :tabnew<CR>  
"列出当前目录文件  
map <F3> :tabnew .<CR>  
"打开树状文件目录  
map <C-F3> \be  
"C，C++ 按F5编译运行
map <F5> :call CompileRunGcc()<CR>
func! CompileRunGcc()
    exec "w"
    if &filetype == 'c'
        exec "!g++ % -o %<"
        exec "! ./%<"
    elseif &filetype == 'cpp'
        exec "!g++ % -o %<"
        exec "! ./%<"
    elseif &filetype == 'java' 
        exec "!javac %" 
        exec "!java %<"
    elseif &filetype == 'sh'
        :!./%
    endif
endfunc
"C,C++的调试
map <F8> :call Rungdb()<CR>
func! Rungdb()
    exec "w"
    exec "!g++ % -g -o %<"
    exec "!gdb ./%<"
endfunc



