call plug#begin('~/.config/nvim/plugged')
  Plug 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }
  Plug 'junegunn/fzf.vim'
  Plug 'rking/ag.vim'
  Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
  Plug 'w0rp/ale'
  Plug 'tpope/vim-surround'
  Plug 'tpope/vim-repeat'
  Plug 'haishanh/night-owl.vim'
  Plug 'luochen1990/rainbow'
  Plug 'pangloss/vim-javascript'
  Plug 'mxw/vim-jsx'
  Plug 'cohama/lexima.vim'
  Plug 'HerringtonDarkholme/yats.vim'
	Plug 'mhartington/nvim-typescript', {'do': './install.sh'}

  if has('nvim')
    Plug 'Shougo/deoplete.nvim', { 'do': ':UpdateRemotePlugins' }
  else
    Plug 'Shougo/deoplete.nvim'
    Plug 'roxma/nvim-yarp'
    Plug 'roxma/vim-hug-neovim-rpc'
  endif
  " post install (yarn install | npm install)
  Plug 'prettier/vim-prettier', { 'do': 'npm install' }
call plug#end()

let g:rainbow_active = 1 

"set leader to space
nmap <Space> <leader>

filetype plugin indent on
" On pressing tab, insert 2 spaces
set expandtab
" show existing tab with 2 spaces width
set tabstop=2
set softtabstop=2
" when indenting with '>', use 2 spaces width
set shiftwidth=2
set shiftround

"use ctrl p for finding files
nnoremap <C-p> :FZF<CR>

"turn off line wrapping
set nowrap

"show line numbers
set number

"keep cursor centered always
nnoremap j jzz
nnoremap k kzz
nnoremap G Gzz
nnoremap } }zz
nnoremap { {zz
nnoremap n nzz
nnoremap N Nzz



"autoClose braces/quotes
"inoremap " ""<left>
"inoremap ' ''<left>
"inoremap ( ()<left>
"inoremap [ []<left>
"inoremap { {}<left>
"inoremap {<CR> {<CR>}<ESC>O
"inoremap {;<CR> {<CR>};<ESC>O

"map aliases from zsh for easy usage in vi
"
"npm run build
nnoremap <C-b> :!b <CR>
"npm run test
nnoremap <C-t> :!t <CR>
"git status
nnoremap <C-g> :!gs <CR>


" leader is set to space at the top of this file
" this means that we can trigger custom commands 
" using spacebar+somekey when in normal mode
nnoremap <leader>gpl :!git pull <CR>
nnoremap <leader>n :NERDTreeToggle <CR>
nnoremap <leader>w :w <CR>
nnoremap <leader>q :q!
nnoremap <leader>i :!npm i <CR>
nnoremap <leader>b :w <CR> :!rm -rf build && b <CR>
nnoremap <leader>t :term t <CR>
nnoremap <leader>gp :!gp <CR>
nnoremap <leader>gs :!gs <CR>


"use NERDTree if opening a directory
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 1 && isdirectory(argv()[0]) && !exists("s:std_in") | exe 'NERDTree' argv()[0] | wincmd p | ene | exe 'cd '.argv()[0] | endif

let NERDTreeQuitOnOpen=1


"enable deoplete
let g:deoplete#enable_at_startup = 1

let g:ale_fixers = {
 \ 'javascript': ['eslint']
 \ }
 
let g:ale_sign_error = '❌'
let g:ale_sign_warning = '⚠️'

let g:ale_fix_on_save = 1

"use <tab> for completion
function! TabWrap()
    if pumvisible()
        return "\<C-N>"
    elseif strpart( getline('.'), 0, col('.') - 1 ) =~ '^\s*$'
        return "\<tab>"
    elseif &omnifunc !~ ''
        return "\<C-X>\<C-O>"
    else
        return "\<C-N>"
    endif
endfunction

" power tab
imap <silent><expr><tab> TabWrap()

" Enter: complete&close popup if visible (so next Enter works); else: break undo
inoremap <silent><expr> <Cr> pumvisible() ?
            \ deoplete#mappings#close_popup() : "<C-g>u<Cr>"

" Ctrl-Space: summon FULL (synced) autocompletion
inoremap <silent><expr> <C-Space> deoplete#mappings#manual_complete()

" Escape: exit autocompletion, go to Normal mode
inoremap <silent><expr> <Esc> pumvisible() ? "<C-e><Esc>" : "<Esc>"

let g:ale_linters = {'javascript': ['eslint']}

if (has("termguicolors"))
 set termguicolors
endif

syntax enable
colorscheme night-OWL


"move line up
nnoremap _ ddkP
nnoremap - ddpzz

nnoremap <c-u> <esc>viwUea
inoremap <c-u> viwUea
nnoremap <leader>ev :split $MYVIMRC<cr>
nnoremap <leader>sv :source $MYVIMRC<cr>
nnoremap <leader>wq :wq<cr>
