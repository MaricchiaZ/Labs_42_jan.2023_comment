all:
	@make --no-print-directory -C ./encoder all
	@make --no-print-directory -C ./decoder all
	@cp ./encoder/encoder ./bin/
	@cp ./decoder/decoder ./bin/

clean:
	@make --no-print-directory -C ./encoder clean
	@make --no-print-directory -C ./decoder clean

fclean: clean
	@make --no-print-directory -C ./encoder fclean
	@make --no-print-directory -C ./decoder fclean

re: fclean all

.PHONY: all clean fclean re