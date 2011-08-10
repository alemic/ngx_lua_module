
/*
 * Copyright (C) Ngwsx
 */


#ifndef _NGX_LUA_MODULE_H_INCLUDED_
#define _NGX_LUA_MODULE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


typedef struct {
    ngx_str_t       path;
    ngx_str_t       cpath;
    lua_State      *l;
} ngx_lua_main_conf_t;


typedef struct {
    ngx_file_t      file;
    size_t          size;
    ngx_str_t       path;
    ngx_buf_t      *lsp;
    ngx_buf_t      *buf;

    ngx_chain_t    *out;
    ngx_chain_t    *last;

    lua_State      *l;
    int             ref;

    ngx_str_t       request_body;
} ngx_lua_ctx_t;


typedef struct {
    char           *name;
    int             value;
} ngx_lua_const_t;


ngx_int_t ngx_lua_state_new(ngx_conf_t *cf, ngx_lua_main_conf_t *lmcf);
void ngx_lua_state_close(void *data);

ngx_int_t ngx_lua_thread_new(ngx_http_request_t *r, ngx_lua_ctx_t *ctx);
void ngx_lua_thread_close(ngx_http_request_t *r, ngx_lua_ctx_t *ctx);
ngx_int_t ngx_lua_thread_run(ngx_http_request_t *r, ngx_lua_ctx_t *ctx, int n);

ngx_http_request_t *ngx_lua_request(lua_State *l);
ngx_int_t ngx_lua_output(ngx_http_request_t *r, u_char *buf, size_t size);
void ngx_lua_finalize(ngx_http_request_t *r, ngx_int_t rc);

ngx_int_t ngx_lua_parse(ngx_http_request_t *r, ngx_lua_ctx_t *ctx);

void ngx_lua_api_init(lua_State *l);
void ngx_lua_dbd_api_init(lua_State *l);
void ngx_lua_file_api_init(lua_State *l);
void ngx_lua_logger_api_init(lua_State *l);
void ngx_lua_request_api_init(lua_State *l);
void ngx_lua_response_api_init(lua_State *l);
void ngx_lua_session_api_init(lua_State *l);
void ngx_lua_socket_api_init(lua_State *l);
void ngx_lua_variable_api_init(lua_State *l);


extern ngx_module_t  ngx_lua_module;


#endif /* _NGX_LUA_MODULE_H_INCLUDED_ */