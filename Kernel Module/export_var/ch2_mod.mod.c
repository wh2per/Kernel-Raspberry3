#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x367398b6, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x1a96fe1c, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x12d86225, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xb3f5c92f, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xc399c8d4, __VMLINUX_SYMBOL_STR(number) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ch1_mod";


MODULE_INFO(srcversion, "9CB3868AA45D199E83273EF");
