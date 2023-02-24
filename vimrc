" 输入设置
set backspace=2
set tabstop=2
set shiftwidth=2
set smarttab
set expandtab

" 缩进设置
set autoindent
set smartindent
set cindent
set cinoptions=g1,h1,i4,l1,m1,N-s,t0,W4,+2s,:2,(0

" 显示设置
" support gnu syntaxt
let c_gnu = 1

" 行宽不要超过120
let &colorcolumn="121"

" show error for mixed tab-space
let c_space_errors = 1
"let c_no_tab_space_error = 1

" don't show gcc statement expression ({x, y;}) as error
let c_no_curly_error = 1

" 缩进格式修正：模板参数表，类初始化列表等
function! FixCppIndent()
    let l:cline_num = line('.')
    let l:cline = getline(l:cline_num)
    let l:pline_num = prevnonblank(l:cline_num - 1)
    let l:pline = getline(l:pline_num)
    while l:pline =~# '\(^\s*{\s*\|^\s*//\|^\s*/\*\|\*/\s*$\)'
        let l:pline_num = prevnonblank(l:pline_num - 1)
        let l:pline = getline(l:pline_num)
    endwhile
    let l:retv = cindent('.')
    let l:pindent = indent(l:pline_num)
    if l:pline =~# '^\s*template\s*<\s*$'
        let l:retv = l:pindent + &shiftwidth
    elseif l:pline =~# '^\s*template\s*<.*>\s*$'
        let l:retv = l:pindent
    elseif l:pline =~# '\s*typename\s*.*,\s*$'
        let l:retv = l:pindent
    elseif l:pline =~# '\s*typename\s*.*>\s*$'
        let l:retv = l:pindent - &shiftwidth
    elseif l:cline =~# '^\s*>\s*$'
        let l:retv = l:pindent - &shiftwidth
    elseif l:pline =~# '^\s\+: \S.*' " C++ initialize list
        let l:retv = l:pindent + 2
    elseif l:cline =~# '^\s*:\s*\w\+(' " C++ initialize list
        let l:retv = l:pindent + 4
    else
        echo "No match"
    endif
    return l:retv
endfunction
autocmd FileType cpp nested setlocal indentexpr=FixCppIndent()

" 保存时自动删除行尾多余的空白字符
function! RemoveTrailingSpace()
    if $VIM_HATE_SPACE_ERRORS != '0'
        normal m`
        silent! :%s/\s\+$//e
        normal ``
    endif
endfunction
autocmd BufWritePre * nested call RemoveTrailingSpace()

" 修复不一致的换行符，统一采用 Unix 换行符(\n)
function! FixInconsistFileFormat()
    if &fileformat == 'unix'
        silent! :%s/\r$//e
    endif
endfunction
autocmd BufWritePre * nested call FixInconsistFileFormat()

" 增加'CppLint'自定义命令，在冒号模式下输入:CppLint即可检查当前文件，也支持带文件名参数。
" 检查结果支持 vim 的  QuickFix 模式，在不离开 vim 的情况下跳转到出错行方便，修正。
function! CppLint(...)
    let l:args = join(a:000)
    if l:args == ""
        let l:args = expand("%")
        if l:args == ""
            let l:args = '*'
        endif
    endif
    let l:old_makeprg = &makeprg
    setlocal makeprg=cpplint.py
    execute "make " . l:args
    let &makeprg=old_makeprg
endfunction
command! -complete=file -nargs=* CppLint call CppLint('<args>')

set tags=./tags;,.tags
" Specify a directory for plugins
" " - For Neovim: stdpath('data') . '/plugged'
" " - Avoid using standard Vim directory names like 'plugin'
call plug#begin('~/.vim/plugged')
Plug 'junegunn/vim-easy-align'
Plug 'skywind3000/quickmenu.vim'
Plug 'skywind3000/asyncrun.vim'
"Plug 'dense-analysis/ale'
Plug 'kana/vim-textobj-user'
Plug 'kana/vim-textobj-indent'
Plug 'kana/vim-textobj-syntax'
Plug 'kana/vim-textobj-function', {'for':['c', 'cpp', 'cc']}
Plug 'sgur/vim-textobj-parameter'
Plug 'octol/vim-cpp-enhanced-highlight'
Plug 'scrooloose/nerdtree', {'on': 'NERDTreeToggle'}
Plug 'tpope/vim-fireplace', {'for': 'clojure'}
Plug 'rdnetto/YCM-Generator', {'branch': 'stable'}
Plug 'frazrepo/vim-rainbow', {'branch': 'master'}
Plug 'rhysd/vim-clang-format', {'branch': 'master'}
Plug 'kana/vim-operator-user',
call plug#end()

let mapleader=","

"###########################################################################
""rainbow
let g:rainbow_active = 1

let g:rainbow_load_separately = [
    \ [ '*' , [['(', ')'], ['\[', '\]'], ['{', '}']] ],
    \ [ '*.tex' , [['(', ')'], ['\[', '\]']] ],
    \ [ '*.cpp' , [['(', ')'], ['\[', '\]'], ['{', '}']] ],
    \ [ '*.{html,htm}' , [['(', ')'], ['\[', '\]'], ['{', '}'], ['<\a[^>]*>', '</[^>]*>']] ],
    \ ]

let g:rainbow_guifgs = ['RoyalBlue3', 'DarkOrange3', 'DarkOrchid3', 'FireBrick']
let g:rainbow_ctermfgs = ['lightblue', 'lightgreen', 'yellow', 'red', 'magenta']
"###########################################################################

"###########################################################################
"nerdtree
" 关闭NERDTree快捷键
map <leader>n :NERDTreeToggle<CR>
" 显示行号
let NERDTreeShowLineNumbers=1
let NERDTreeAutoCenter=1
" 是否显示隐藏文件
let NERDTreeShowHidden=1
" 设置宽度
let NERDTreeWinSize=35
" 在终端启动vim时，共享NERDTree
let g:nerdtree_tabs_open_on_console_startup=1
" 忽略一下文件的显示
let NERDTreeIgnore=['\.pyc','\~$','\.swp']
" 显示书签列表
let NERDTreeShowBookmarks=1
"打开vim时如果没有文件自动打开NERDTree
autocmd vimenter * if !argc()|NERDTree|endif
""当NERDTree为剩下的唯一窗口时自动关闭
autocmd bufenter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif
let NERDTreeMinimalUI = 1
let NERDTreeDirArrows = 1


"###########################################################################
set nu
syntax enable
set history=500
set ruler
"set mouse=a
set smarttab
set fencs=utf-8
set fileencodings=utf-8
set termencoding=utf-8
set nobackup
set nowritebackup
"set noswapfile
set nowb
set showmatch
set completeopt=longest,menu
set magic
set number
set cursorline
"set cursorcolumn
set incsearch
set hlsearch
set backspace=indent,eol,start
"set tabstop=4 expandtab
set shiftwidth=2
set autoindent
set smartindent
set wrap
set foldenable
setlocal foldlevel=1
set foldmethod=indent
set foldlevelstart=99
nnoremap <space> @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo')<CR>

" 自动定位上上次打开位置
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif

"" " clang-format
"" function! Formatonsave()
""   let l:formatdiff = 1
""   let g:clang_format_fallback_style="/Users/zhaoxiaosen/.clang-format"
""   pyf /usr/local/Cellar/clang-format/15.0.7/share/clang/clang-format.py
"" endfunction
"" autocmd BufWritePre *.h,*.cc,*.cpp call Formatonsave()

let g:clang_format#style_options = {
  \ "Language" : "Cpp",
            \ "BasedOnStyle" : "Google",
            \ "ColumnLimit" : "120",
            \ "DerivePointerAlignment" : "false",
            \ "PointerAlignment" : "Left",
            \ "SortIncludes" : "true",
            \ "IncludeBlocks" : "Preserve",
            \ "IndentPPDirectives" : "AfterHash",
            \ "SpacesBeforeTrailingComments" : "2"}

" map to <Leader>cf in C++ code
autocmd FileType c,cpp,cc,h nnoremap <buffer><Leader>cf :<C-u>ClangFormat<CR>
autocmd FileType c,cpp,cc,h vnoremap <buffer><Leader>cf :ClangFormat<CR>
" Toggle auto formatting:
nmap <Leader>c :ClangFormat<CR>
autocmd FileType c,cpp,cc,h map <buffer><Leader>x <Plug>(operator-clang-format)

function! Formatonsave()
  exec "ClangFormat"
endfunction
autocmd BufWritePre *.h,*.cc,*.cpp call Formatonsave()


