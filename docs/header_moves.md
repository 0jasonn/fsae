# Header moves (2026-11-20)

The restructure moved and folded headers (commits 22339f0, b945c3a, b654b13). Use this to fix includes in
work-in-progress drafts. Moved headers keep their contents; deleted grab-bag headers had their declarations moved to the
header of the module that defines each function (or include/engine/functions.h for undecompiled code).

## Moved

| old | new |
|---|---|
| actor/enemy/ending.h | game/ending.h |
| actor/enemy/ending_scene.h | game/ending_scene.h |
| actor/object/knife_comm_skip.h | knife/comm/knife_comm_skip.h |
| actor/object/objutil_5.h | engine/objutil_5.h |
| actor/object/oplogo_shadow.h | ui/oplogo_shadow.h |
| actor/object/setmisc.h | game/multiroom.h |
| actor/object/sound_api.h | engine/sound/sound_api.h |
| actor/object/sound_req.h | engine/sound/sound_req.h |
| actor/object/wm_idle2parent.h | knife/comm/wm_idle2parent.h |
| engine/card.h | sdk/card/card.h |
| engine/cardbus_lock_api.h | sdk/os/cardbus_lock_api.h |
| engine/device_flags_api.h | sdk/os/device_flags_api.h |
| engine/dma_conflict_api.h | sdk/mi/dma_conflict_api.h |
| engine/engine_block_api.h | sdk/rtc/rtc.h |
| engine/engine_halfb_api.h | sdk/os/engine_halfb_api.h |
| engine/engine_halfc_api.h | sdk/os/engine_halfc_api.h |
| engine/engine_romword_api.h | sdk/fatfs/engine_romword_api.h |
| engine/engine_word_api.h | sdk/fatfs/engine_word_api.h |
| engine/fatfs_wrap_api.h | sdk/fatfs/fatfs_wrap_api.h |
| engine/field_kind_api.h | sdk/gx/field_kind_api.h |
| engine/fs_open.h | sdk/fs/fs_open.h |
| engine/fs_wrap_api.h | sdk/fs/fs_wrap_api.h |
| engine/irqcount_api.h | sdk/os/irqcount_api.h |
| engine/mpu_api.h | sdk/os/mpu_api.h |
| engine/mutex_wrap_api.h | sdk/snd/mutex_wrap_api.h |
| engine/obj_get24_api.h | sdk/fs/obj_get24_api.h |
| engine/obj_get38_api.h | sdk/snd/obj_get38_api.h |
| engine/os_blocking_mode_api.h | ui/os_blocking_mode_api.h |
| engine/os_halt_api.h | sdk/os/os_halt_api.h |
| engine/os_irq_flush_api.h | sdk/os/os_irq_flush_api.h |
| engine/os_kind_terminate_api.h | sdk/os/os_kind_terminate_api.h |
| engine/os_sleep_api.h | sdk/os/os_sleep_api.h |
| engine/os_switch_api.h | sdk/os/os_switch_api.h |
| engine/os_thread.h | sdk/os/os_thread.h |
| engine/os_thread_exit_api.h | sdk/os/os_thread_exit_api.h |
| engine/os_wrap_api.h | sdk/os/os_wrap_api.h |
| engine/pair_block.h | sdk/os/pair_block.h |
| engine/pair_get_api.h | sdk/os/pair_get_api.h |
| engine/pair_restore_api.h | sdk/os/pair_restore_api.h |
| engine/pair_setup_api.h | sdk/os/pair_setup_api.h |
| engine/pm_callback_api.h | sdk/pm/pm_callback_api.h |
| engine/pmi_send.h | sdk/pm/pmi_send.h |
| engine/pmi_send_api.h | sdk/pm/pmi_send_api.h |
| engine/ret_code_alt_api.h | sdk/fs/ret_code_alt_api.h |
| engine/ret_const_api.h | sdk/fs/ret_const_api.h |
| engine/ret_one_api.h | sdk/os/ret_one_api.h |
| engine/slot_group_api.h | ui/widget/slot_group_api.h |
| engine/std_snprintf_api.h | sdk/std/std_snprintf_api.h |
| engine/stdconv_table_wrap_api.h | sdk/fatfs/stdconv_table_wrap_api.h |
| engine/stdconv_wrap_api.h | sdk/fs/stdconv_wrap_api.h |
| engine/stub_init_api.h | sdk/init/stub_init_api.h |
| engine/stub_noop_a_api.h | knife/comm/stub_noop_a_api.h |
| engine/stub_noop_b_api.h | knife/comm/stub_noop_b_api.h |
| engine/stub_zero_a_api.h | knife/comm/stub_zero_a_api.h |
| engine/stub_zero_b_api.h | knife/comm/stub_zero_b_api.h |
| engine/vram_bank_bits_api.h | sdk/gx/vram_bank_bits_api.h |
| engine/vrambank_api.h | sdk/gx/vrambank_api.h |
| engine/wm_datasharing.h | sdk/wm/wm_datasharing.h |
| engine/wm_send_callback.h | sdk/wm/wm_send_callback.h |
| engine/wm_startmp.h | sdk/wm/wm_startmp.h |
| game/boots.h | actor/object/boots.h |
| game/doorsel_4.h | ui/doorsel_4.h |
| game/doorsel_appear.h | ui/doorsel_appear.h |
| game/doorsel_exit.h | ui/doorsel_exit.h |
| game/doorsel_init.h | ui/doorsel_init.h |
| game/exchange_savedata_api.h | ui/exchange_savedata_api.h |
| game/wanwan.h | actor/object/wanwan.h |
| knife/app/knifeinfo_api.h | knife/message/knifeinfo_api.h |
| ui/selectiondialog.h | knife/message/selectiondialog.h |

## Deleted (declarations now live with their owners)

| deleted | where its declarations went (main owners) |
|---|---|
| actor/enemy/decls_b.h | actor/enemy/em18_2.h, actor/enemy/em1d_possess.h, engine/com_work.h, ui/doorsel_4.h, knife/comm/com.h, knife/comm/comm.h |
| actor/enemy/decls_b2.h | engine/functions.h, ui/widget/menu_release.h, game/agent.h, game/bg_info.h, game/cockpit_9.h, game/hit.h |
| actor/enemy/em19_api.h | actor/enemy/em19.h, actor/enemy/em19_6.h |
| actor/enemy/em2a_api.h | actor/enemy/em2a.h |
| actor/enemy/ending_scene_00.h | engine/droprupees.h, engine/functions.h, engine/objutil_5.h, engine/vgroup_slots.h, game/agent.h, game/before_player.h |
| actor/object/actor_calls_k.h | actor/object/yuka_api.h, engine/droprupees.h, engine/functions.h, actor/object/arrow.h, engine/objutil.h |
| actor/object/c_decls_2.h | engine/functions.h, game/shikake.h, knife/subtask/game_start.h, actor/enemy/demo_loader.h, engine/irq.h, game/check.h |
| actor/object/cellcalls.h | engine/functions.h, actor/object/nemoto_3.h |
| actor/object/common_a.h | engine/functions.h, engine/cockpit_state.h, game/cockpit.h, game/cockpitdata.h, game/cockpit_bg_trans.h, engine/map_state.h |
| actor/object/effectdecls.h | actor/object/set46.h, engine/functions.h |
| actor/object/fdecls.h | engine/backup_media.h, engine/bg_buff.h, engine/bg_load.h, engine/blend_request.h, engine/cockpit_state.h, engine/com_work.h |
| actor/object/g_callees.h | engine/functions.h, actor/object/ido_yuka.h, actor/object/set13_cell.h, actor/object/yuka_api.h, actor/object/ido.h, engine/entity.h |
| actor/object/k_bitstream.h | engine/bitstream.h, knife/message/knife_message_term.h |
| actor/object/k_misc.h | engine/droprupees.h, engine/functions.h, engine/objutil_5.h, engine/vgroup_slots.h, game/agent.h, game/before_player.h |
| actor/object/k_yousei.h | game/yousei.h, game/rupeelevel.h, engine/player.h, game/clearkey.h |
| actor/object/objdecls.h | engine/functions.h, actor/object/rewdoor_knife.h, engine/bg_buff.h, engine/com_work.h, engine/display_state.h, engine/effect_state.h |
| actor/object/objdecls_a.h | engine/functions.h, game/multiplay.h, game/keyclear_api.h, actor/object/zeldafade.h, engine/vgroup_slots.h, game/cockpit_9.h |
| actor/object/objdecls_f.h | engine/functions.h, actor/object/nemoto_3.h, game/ranking.h, game/pl_start_pos.h, game/keyclear_api.h, game/multiplay.h |
| actor/object/objdispatch_api.h | actor/object/objdispatch.h |
| actor/object/protos.h | engine/functions.h, knife/comm/single_play.h, actor/object/pot.h, engine/em12_type_masks.h, actor/enemy/encnt.h, actor/object/set29.h |
| actor/object/setcommon_g.h | engine/entity.h, engine/functions.h, engine/oam_ring.h, game/agent.h, game/bg_info.h, game/cockpit.h |
| actor/object/shield_decls.h | engine/local_player_index.h, actor/object/shield.h |
| actor/object/singleplay_api.h | knife/comm/singleplay.h |
| actor/object/tama0f_api.h | engine/functions.h, actor/object/tama0f.h |
| actor/object/tama0f_decls.h | engine/bg_buff.h, engine/blend_request.h, engine/display_state.h, engine/droprupees.h, engine/entity.h, engine/functions.h |
| actor/object/tama_decls.h | engine/functions.h, actor/enemy/em2e.h |
| engine/a_decls.h | engine/functions.h, actor/enemy/rewcell_one.h, ui/stagesel_common.h, ui/widget/ctrl_loadbg.h, knife/comm/wirelessmanager.h, knife/message/knife_font.h |
| engine/a_extern.h | engine/functions.h, engine/record_cursor.h |
| engine/callees.h | engine/functions.h, engine/objwork.h, game/agent.h, game/cockpitdata.h, ui/opdemo.h, ui/widget/ctrl_loadbg.h |
| engine/common_d.h | engine/player.h, game/cockpitdata.h, ui/stagesel_common.h, actor/enemy/em09.h |
| engine/decls_a.h | engine/vgroup.h, game/cockpitdata.h, game/cockpit_9.h, game/map.h, game/savemedia.h, game/shikake.h |
| engine/g_calls.h | engine/functions.h, engine/fs_dirfile_api.h, engine/sound/sndsys_api.h, knife/comm/change_buffer.h |
| engine/k_decls.h | engine/entry_check.h, actor/object/set67_init.h, ui/nameentryui_checkspace.h |
| engine/record_init_api.h | engine/record_init.h |
| engine/sdk_wrap.h | engine/functions.h, sdk/card/card.h, game/savemedia.h, knife/app/knife_file_2.h |
| engine/sound/m4a_api.h | engine/sound/m4a.h |
| engine/sound/sndrecord_api.h | engine/sound/sndrecord.h |
| engine/stub_empty_api.h | sdk/os/stub_empty.h, sdk/fx/stub_empty.h |
| engine/wm_api.h | engine/functions.h, sdk/wm/wm_sleep.h, sdk/pm/pm.h, sdk/wm/wm_system.h, sdk/wm/wm_enable.h, knife/comm/wirelessmgr.h |
| game/b_extra.h | engine/functions.h, actor/object/zeldafade.h, knife/app/knife_file_2.h, knife/app/twl.h |
| game/backup_api.h | game/backup.h |
| game/decls_e.h | ui/groupselectuiview.h, knife/message/textrender.h, knife/app/knife_app.h, engine/functions.h, knife/message/text_tokenizer.h, knife/subtask/subtask_work.h |
| game/decls_g.h | engine/functions.h, ui/widget/menu.h, knife/subtask/game_start.h, knife/message/texttags.h, knife/message/text_tokenizer.h, engine/sound/m4a.h |
| game/doorsel.h | ui/doorsel.h, ui/doorsel_4.h |
| game/hitdecls.h | engine/functions.h, game/hit.h, game/cockpit.h, game/iroyuka_2.h, game/rankingsave.h, actor/object/bomb.h |
| game/map_api.h | game/map.h, actor/enemy/rewcell_one.h |
| game/shikake_api.h | game/shikake.h |
| knife/app/knife_app_api.h | knife/app/knife_app.h |
| knife/app/knife_hud_api.h | knife/app/knife_hud.h |
| knife/app/knife_manual_api.h | (nothing left: unused) |
| knife/app/knife_power_5_api.h | knife/app/knife_power.h |
| knife/comm/com_api.h | knife/comm/com.h |
| knife/comm/comm_parentinfo_api.h | knife/comm/comm_parentinfo.h |
| knife/comm/single_play_api.h | knife/comm/single_play.h |
| knife/comm/singleplay_api.h | engine/functions.h, actor/enemy/em30.h, knife/comm/singleplay_movepartner.h, engine/objwork.h, game/agent.h, game/cockpitdata.h |
| knife/comm/wireless_manager_api.h | knife/comm/wireless_manager.h |
| knife/comm/wm_connect_2_api.h | knife/comm/wm_connect_api.h |
| knife/message/groupcreate_api.h | knife/message/groupcreate.h, knife/message/gcm_nc.h, knife/message/groupcreateui_move.h, knife/message/modeselui_main.h, engine/com_work.h, knife/message/playstyle_update.h |
| knife/message/knife_message_api.h | knife/message/knife_message.h |
| knife/message/textlength_api.h | knife/message/textlength.h |
| knife/message/textreader_api.h | knife/message/textreader.h |
| knife/message/textrender_api.h | knife/message/textrender.h |
| knife/sound/knife_sound_api.h | knife/sound/knife_sound.h |
| knife/subtask/subtask_calls.h | engine/functions.h, game/bg_info.h, knife/subtask/subtask_data.h, knife/subtask/subtask_init_bg.h, knife/subtask/subtask.h, ui/widget/ctrl_loadbg.h |
| knife/subtask/subtask_init_api.h | knife/subtask/subtask_init.h |
| ui/doorsel_api.h | ui/doorsel.h |
| ui/fileselui_2_api.h | ui/fileselui.h |
| ui/fileselui_api.h | ui/fileselui.h |
| ui/groupcreateui_api.h | ui/groupcreateui.h |
| ui/groupselectuiview_api.h | ui/groupselectuiview.h |
| ui/lobby_api.h | ui/lobby.h |
| ui/modeselui_api.h | ui/modeselui.h |
| ui/msgwin_decls.h | types.h, engine/backup_media.h, engine/bg_buff.h, engine/bg_char.h, engine/bg_load.h, engine/bg_palette_api.h |
| ui/opdemo_api.h | ui/opdemo.h, engine/effect_state.h |
| ui/selectiondialog_api.h | knife/message/selectiondialog.h |
| ui/widget/baseduiview_api.h | ui/widget/baseduiview.h |
| ui/widget/menu_api.h | ui/widget/menu.h, engine/menusound.h |
| ui/widget/rect_f.h | engine/functions.h, game/bg_info.h, ui/widget/rect_links.h, ui/widget/rect_create.h, knife/subtask/subtask_init_bg.h, engine/oam_ring.h |
| ui/widget/rect_item_api.h | ui/widget/rect_item.h |
| ui/widget/rect_list_api.h | ui/widget/rect_list.h |
| ui/widget/tile_map_api.h | ui/widget/tile_map.h |
