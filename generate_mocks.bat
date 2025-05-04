@echo off
setlocal

echo Generating mocks...

ruby -I CMock-master/lib CMock-master/scripts/create_mock.rb src/data/account_data.h -o cmock_config.yml
ruby -I CMock-master/lib CMock-master/scripts/create_mock.rb src/logic/create_account.h -o cmock_config.yml
ruby -I CMock-master/lib CMock-master/scripts/create_mock.rb src/presentation/user_interface.h -o cmock_config.yml

echo All mocks generated in the 'mocks' folder.
pause
