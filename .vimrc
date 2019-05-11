set nocompatible              "  这是必需的 
filetype off                  " 这是必需的 
set number "显示行号
set nowrap   "不换行 
set shiftwidth=4 "默认缩进4个空格 
set softtabstop=4 "使用tab时 tab空格数
set tabstop=4  "tab代表4个空格 
set laststatus=2  "总是显示状态行 




""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 你在此设置运行时路径 

set rtp+=~/.vim/bundle/Vundle.vim 
" vundle初始化 
call vundle#begin()  
"  " 这应该始终是第一个 
Plugin 'gmarik/Vundle.vim'

Bundle 'altercation/vim-colors-solarized'
Plugin 'vim-scripts/OmniCppComplete'
Plugin 'Valloric/YouCompleteMe'

Plugin 'scrooloose/nerdtree'

"每个插件都应该在这一行之前   
call vundle#end()            " required 

let g:ycm_global_ycm_extra_conf='~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py'



""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set nocompatible
set backspace=indent,eol,start

"设置自动补全括号""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
inoremap ' ''<ESC>i
inoremap " ""<ESC>i
inoremap ( ()<ESC>i
inoremap [ []<ESC>i
inoremap < <><ESC>i
inoremap { {<CR>}<ESC>O
"设置跳出括号
""func SkipPair()  
""    if getline('.')[col('.') - 1] == ')' || getline('.')[col('.') - 1] == ']' || getline('.')[col('.') - 1] == '"' || getline('.')[col('.') - 1] == "'" || getline('.')[col('.') - 1] == '}'  
""	        return "\<ESC>la"  
""	else  
""			return "\t"  
""	endif  
""endfunc  
" 将tab键绑定为跳出括号  
""inoremap <TAB> <c-r>=SkipPair()<CR>
""backspace键 
" indent 删除自动缩进的值
" eol 删除上一行行末尾的回车，两行合并 
" start 除了刚输入的，还删除原来的字符
" set backspace=indent,eol,start
"set expandtab "使用空格替换tab 


""""""颜色主题""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set autoindent " 自动缩进"

""colorscheme elflord   

""colorscheme desert
""colorscheme evening
""colorscheme murphy
"colorscheme morning
"colorscheme pablo
""colorscheme darkdot
""colorscheme jhdark
""colorscheme SolarizedDark
hi Normal guibg=NONE ctermbg=NONE
""colorscheme nightflight
colorscheme graywh
""colorscheme monokai
syn on "语法高亮 

filetype on "文件类型 

set encoding=utf-8 "编码为utf8








""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" nerdtree 配置
" NerdTree才插件的配置信息
""将F2设置为开关NERDTree的快捷键
map <f2> :NERDTreeToggle<cr>
" ""修改树的显示图标 
let g:NERDTreeDirArrowExpandable = '+'
let g:NERDTreeDirArrowCollapsible = '-'
" ""窗口位置
let g:NERDTreeWinPos='left'
" ""窗口尺寸
let g:NERDTreeSize=30
" ""窗口是否显示行号
let g:NERDTreeShowLineNumbers=1
" ""不显示隐藏文件
let g:NERDTreeHidden=0




"""""""自动插入头文件"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"新建.c,.h,.sh,.java文件，
autocmd BufNewFile *.cpp,*.[ch],*.sh,*.java exec ":call SetTitle()" 
"""定义函数SetTitle，自动插入文件头 
func SetTitle() 
""如果文件类型为.sh文件 
	if &filetype == 'sh' 
		call setline(1, "##########################################################################") 
		call append(line("."), "# File Name: ".expand("%")) 
		call append(line(".")+1, "# Author: top-down") 
		call append(line(".")+2,"> Description: ") 
		call append(line(".")+3, "# Created Time: ".strftime("%c")) 
		call append(line(".")+4, "#########################################################################") 
		call append(line(".")+5, "#!/bin/zsh")
		call append(line(".")+6, "PATH=/home/edison/bin:/home/edison/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/work/tools/gcc-3.4.5-glibc-2.3.6/bin")
		call append(line(".")+7, "export PATH")
		call append(line(".")+8, "")
	else 
		call setline(1, "/*▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩") 
		call append(line("."), "▩ File Name: ".expand("%"))												
		call append(line(".")+1, "▩ Author: top-down")													
		call append(line(".")+2,"▩ Description: ")														
		call append(line(".")+3, "▩ Created Time: ".strftime("%c"))										
		call append(line(".")+4, "▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩*/") 
		call append(line(".")+5, "")
	endif
	if &filetype == 'cpp'
		call append(line(".")+6, "#include<iostream>")
		call append(line(".")+7, "using namespace std;")
		call append(line(".")+8, "")
		endif
	if &filetype == 'c'
		call append(line(".")+6, "#include<stdio.h>")
		call append(line(".")+7, "")
	endif
		if &filetype == 'java'
		call append(line(".")+6,"public class".expand("%"))
		call append(line(".")+7,"")
	endif
	"	"""新建文件后，自动定位到文件末尾
	autocmd BufNewFile * normal G

endfunc 


"""""""""""YCM的配置""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" 寻找全局配置文件
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/cpp/ycm/.ycm_extra_conf.py'
" 禁用syntastic来对python检查
let g:syntastic_ignore_files=[".*\.py$"] 
" 使用ctags生成的tags文件
let g:ycm_collect_identifiers_from_tag_files = 1
" 开启语义补全
" 修改对C语言的补全快捷键，默认是CTRL+space，修改为ALT+;未测出效果
let g:ycm_key_invoke_completion = '<M-;>'
" 设置转到定义处的快捷键为ALT+G，未测出效果
nmap <M-g> :YcmCompleter GoToDefinitionElseDeclaration <C-R>=expand("<cword>")<CR><CR> 
"关键字补全
let g:ycm_seed_identifiers_with_syntax = 1
" 在接受补全后不分裂出一个窗口显示接受的项
set completeopt-=preview
" 让补全行为与一般的IDE一致
set completeopt=longest,menu
" 不显示开启vim时检查ycm_extra_conf文件的信息
let g:ycm_confirm_extra_conf=0
" 每次重新生成匹配项，禁止缓存匹配项
let g:ycm_cache_omnifunc=0
" 在注释中也可以补全
let g:ycm_complete_in_comments=1
" 输入第一个字符就开始补全
let g:ycm_min_num_of_chars_for_completion=1
" 错误标识符
let g:ycm_error_symbol='>!'
" 警告标识符
let g:ycm_warning_symbol='>?'
" 不查询ultisnips提供的代码模板补全，如果需要，设置成1即可
let g:ycm_use_ultisnips_completer=1
""""''"''""""""""">>">")>>""'>'""""""]"''"
let g:ycm_show_diagnostics_ui = 1
