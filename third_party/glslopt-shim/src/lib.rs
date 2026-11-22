//! Pass-through stand-in for the `glslopt` crate: it returns the GLSL source unchanged.
//! Used only in the scratch Firefox 115 MinGW build, because the real crate's C code
//! does not compile against MinGW's pthread header. Shaders are not optimized.

#[derive(Clone, Copy, Debug)]
pub enum Target { OpenGl, OpenGles30 }

#[derive(Clone, Copy, Debug)]
pub enum ShaderType { Vertex, Fragment }

pub struct Context { _target: Target }

impl Context {
    pub fn new(target: Target) -> Context { Context { _target: target } }
    pub fn optimize(&self, _shader_type: ShaderType, source: String) -> Output {
        Output { source }
    }
}

pub struct Output { source: String }

impl Output {
    pub fn get_status(&self) -> bool { true }
    pub fn get_log(&self) -> String { String::new() }
    pub fn get_output(&self) -> Option<&str> { Some(&self.source) }
}
