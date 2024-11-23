local project_path = vim.fn.expand("$RAYTRACING_PATH")

vim.keymap.set("n", "<leader>ab", ":Just build<CR>")
vim.keymap.set("n", "<leader>ar", ":Just run<CR>")

local augroup_nvimrc = vim.api.nvim_create_augroup("nvimrc", { clear = true })
vim.api.nvim_create_autocmd({ "VimEnter" }, {
    pattern = "*",
    group = augroup_nvimrc,
    callback = function(_)
        require("vimrc.dap").init({
            language = "cpp",
            name = "raytracing.cpp",
            program = project_path .. "/build/raytracing.cpp",
            cwd = project_path .. "/build/",
            env = {},
            run_in_terminal = true,
            lldb_dap_path = vim.fn.expand("$LLDB_VS_CODE_PATH"),
        })
    end,
})
